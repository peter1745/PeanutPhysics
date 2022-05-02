#include "PhysicsWorld.h"
#include "Collision/BoxShape.h"
#include "Collision/SphereShape.h"
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
				
				if (actorA->m_InverseMass == 0.0f && actorB->m_InverseMass == 0.0f)
					continue;

				Contact contact;
				if (Intersect(actorA, actorB, contact))
					ResolveContact(contact);
			}
		}

		// Update transform
		for (auto& actor : m_DynamicActors)
			actor->UpdateTransform(deltaTime);
	}

	void PhysicsWorldImpl::ResolveContact(const Contact& contact) const
	{
		DynamicActor actor0 = contact.Actor0.As<DynamicActorImpl>();
		DynamicActor actor1 = contact.Actor1.As<DynamicActorImpl>();

		const float restiution = actor0->m_Restitution * actor1->m_Restitution;

		const glm::mat3 inverseInertiaTensor0 = actor0->GetInverseInertiaTensor();
		const glm::mat3 inverseInertiaTensor1 = actor1->GetInverseInertiaTensor();

		const glm::vec3 pointRelativeToCenter0 = contact.Point0 - actor0->GetCenterOfMass();
		const glm::vec3 pointRelativeToCenter1 = contact.Point1 - actor1->GetCenterOfMass();

		const glm::vec3 angular0 = glm::cross(inverseInertiaTensor0 * glm::cross(pointRelativeToCenter0, contact.Normal), pointRelativeToCenter0);
		const glm::vec3 angular1 = glm::cross(inverseInertiaTensor1 * glm::cross(pointRelativeToCenter1, contact.Normal), pointRelativeToCenter1);
		const float angularFactor = glm::dot(angular0 + angular1, contact.Normal);

		const glm::vec3 velocity0 = actor0->m_LinearVelocity + glm::cross(actor0->m_AngularVelocity, pointRelativeToCenter0);
		const glm::vec3 velocity1 = actor1->m_LinearVelocity + glm::cross(actor1->m_AngularVelocity, pointRelativeToCenter1);

		const glm::vec3 velocityDifference = velocity0 - velocity1;
		const float impulse = (1.0f + restiution) * glm::dot(velocityDifference, contact.Normal) / (actor0->m_InverseMass + actor1->m_InverseMass + angularFactor);
		const glm::vec3 normalImpulse = contact.Normal * impulse;

		actor0->ApplyImpulse(contact.Point0, normalImpulse * -1.0f);
		actor1->ApplyImpulse(contact.Point1, normalImpulse);

		const float t0 = actor0->m_InverseMass / (actor0->m_InverseMass + actor1->m_InverseMass);
		const float t1 = actor1->m_InverseMass / (actor0->m_InverseMass + actor1->m_InverseMass);

		const glm::vec3 distance = contact.Point1 - contact.Point0;
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

		if (actor0->m_Shape->GetType() == ShapeType::Box && actor1->m_Shape->GetType() == ShapeType::Box)
		{
			return IntersectBoxToBox(actor0, actor1, outContact);
		}
		else if (actor0->m_Shape->GetType() == ShapeType::Sphere && actor1->m_Shape->GetType() == ShapeType::Sphere)
		{
			return IntersectSphereToSphere(actor0, actor1, outContact);
		}

		return false;
	}

	bool PhysicsWorldImpl::IntersectBoxToBox(const Ref<ActorBase>& actor0, const Ref<ActorBase>& actor1, Contact& outContact) const
	{
		BoxShape box0 = actor0->m_Shape.As<BoxShapeImpl>();
		BoxShape box1 = actor1->m_Shape.As<BoxShapeImpl>();

		if (!box0 || !box1)
			return false;

		const auto& transform0 = actor0->GetTransform();
		const auto& transform1 = actor1->GetTransform();

		outContact.Point0 = transform0.Location + outContact.Normal * box0->GetHalfExtents();
		outContact.Point1 = transform1.Location - outContact.Normal * box1->GetHalfExtents();

		AABB boundingBox0 = box0->GetBoundingBox();
		AABB boundingBox1 = box1->GetBoundingBox();

		boundingBox0.Translate(actor0->GetTransform().Location);
		boundingBox1.Translate(actor1->GetTransform().Location);

		return boundingBox0.IsOverlaping(boundingBox1);
	}

	bool PhysicsWorldImpl::IntersectSphereToSphere(const Ref<ActorBase>& actor0, const Ref<ActorBase>& actor1, Contact& outContact) const
	{
		SphereShape sphere0 = actor0->m_Shape.As<SphereShapeImpl>();
		SphereShape sphere1 = actor1->m_Shape.As<SphereShapeImpl>();

		if (!sphere0 || !sphere1)
			return false;

		const auto& transform0 = actor0->GetTransform();
		const auto& transform1 = actor1->GetTransform();

		const glm::vec3 distance = transform1.Location - transform0.Location;

		outContact.Point0 = transform0.Location + outContact.Normal * sphere0->GetRadius();
		outContact.Point1 = transform1.Location - outContact.Normal * sphere1->GetRadius();

		const float combinedRadius = sphere0->GetRadius() + sphere1->GetRadius();
		const float lengthSquare = glm::length2(distance);
		return lengthSquare <= combinedRadius * combinedRadius;
	}

}
