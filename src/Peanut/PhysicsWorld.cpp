#include "PhysicsWorld.h"
#include "Collision/BoxShape.h"
#include <iostream>

namespace Peanut {

	PhysicsWorldImpl::PhysicsWorldImpl(const glm::vec3& gravity)
		: m_Gravity(gravity)
	{
	}

	PhysicsWorldImpl::~PhysicsWorldImpl()
	{
		m_DynamicActors.clear();
	}

	void PhysicsWorldImpl::AddActor(const DynamicActor& actor)
	{
		m_DynamicActors.push_back(actor);
	}

	void PhysicsWorldImpl::RemoveActor(const DynamicActor& actor)
	{
		m_DynamicActors.erase(std::find(m_DynamicActors.begin(), m_DynamicActors.end(), actor));
	}

	void PhysicsWorldImpl::Simulate(float deltaTime)
	{
		// Apply gravity
		for (auto& actor : m_DynamicActors)
		{
			if (actor->IsGravityDisabled())
				continue;

			glm::vec3 impulseGravity = m_Gravity * actor->GetMass() * deltaTime;
			actor->ApplyLinearImpulse(impulseGravity);
		}

		// Check for collisions
		for (size_t i = 0; i < m_DynamicActors.size(); i++)
		{
			for (size_t j = i + 1; j < m_DynamicActors.size(); j++)
			{
				auto& actorA = m_DynamicActors[i];
				auto& actorB = m_DynamicActors[j];

				if (actorA == actorB)
					break;

				if (actorA->m_InverseMass == 0.0f || actorB->m_InverseMass == 0.0f)
					continue;

				Contact contact;
				if (Intersect(actorA, actorB, contact))
				{
					ResolveContact(contact);
				}
			}
		}

		// Update positions
		for (auto& actor : m_DynamicActors)
		{
			actor->m_Transform.Location += actor->m_LinearVelocity * deltaTime;
		}
	}

	void PhysicsWorldImpl::ResolveContact(const Contact& contact) const
	{
		DynamicActor actor0 = contact.Actor0.As<DynamicActorImpl>();
		DynamicActor actor1 = contact.Actor1.As<DynamicActorImpl>();
		actor0->m_LinearVelocity = glm::vec3(0.0f);
		actor1->m_LinearVelocity = glm::vec3(0.0f);

		const float t0 = actor0->m_InverseMass / (actor0->m_InverseMass + actor1->m_InverseMass);
		const float t1 = actor1->m_InverseMass / (actor0->m_InverseMass + actor1->m_InverseMass);

		const glm::vec3 distance = contact.WorldSpacePoint1 - contact.WorldSpacePoint0;
		actor0->m_Transform.Location += distance * t0;
		actor1->m_Transform.Location -= distance * t1;
	}

	bool PhysicsWorldImpl::Intersect(const Ref<ActorBase>& actor0, const Ref<ActorBase>& actor1, Contact& outContact) const
	{
		outContact.Actor0 = actor0;
		outContact.Actor1 = actor1;

		const auto& transform0 = actor0->GetTransform();
		const auto& transform1 = actor1->GetTransform();

		const glm::vec3 distance = transform1.Location - transform0.Location;
		outContact.Normal = glm::normalize(distance);

		BoxShape box0 = actor0->m_Shape.As<BoxShapeImpl>();
		BoxShape box1 = actor1->m_Shape.As<BoxShapeImpl>();

		if (!box0 || !box1)
			return false;

		outContact.WorldSpacePoint0 = transform0.Location + outContact.Normal * box0->GetHalfExtents();
		outContact.WorldSpacePoint1 = transform1.Location - outContact.Normal * box1->GetHalfExtents();

		AABB boundingBox0 = box0->GetBoundingBox();
		AABB boundingBox1 = box1->GetBoundingBox();

		boundingBox0.Translate(actor0->GetTransform().Location);
		boundingBox1.Translate(actor1->GetTransform().Location);

		return boundingBox0.IsOverlaping(boundingBox1);
	}

}
