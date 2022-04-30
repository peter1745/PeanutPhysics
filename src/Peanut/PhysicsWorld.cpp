#include "PhysicsWorld.h"

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
		actor->m_ActorID = m_NextActorID++;
		m_DynamicActors.push_back(actor);
	}

	void PhysicsWorldImpl::RemoveActor(const DynamicActor& actor)
	{
		m_DynamicActors.erase(std::find(m_DynamicActors.begin(), m_DynamicActors.end(), actor));
	}

	void PhysicsWorldImpl::Simulate(float deltaTime)
	{
		for (auto& actor : m_DynamicActors)
		{
			actor->m_Force += actor->m_Mass * m_Gravity;
			actor->m_Velocity += actor->m_Force / actor->m_Mass * deltaTime;
			actor->m_Transform.Location += actor->m_Velocity * deltaTime;
			actor->m_Force = glm::vec3(0.0f);
		}
	}
}
