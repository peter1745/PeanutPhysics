#include "PhysicsWorld.h"

namespace Peanut {

	DynamicActor PhysicsWorld::CreateDynamicActor(const Transform& transform)
	{
		DynamicActor actor = std::shared_ptr<DynamicActorImpl>(new DynamicActorImpl(transform));
		actor->m_ActorID = m_NextActorID++;
		m_DynamicActors.push_back(actor);
		return actor;
	}

	void PhysicsWorld::RemoveActor(const DynamicActor& actor)
	{
		m_DynamicActors.erase(std::find(m_DynamicActors.begin(), m_DynamicActors.end(), actor));
	}

	void PhysicsWorld::Simulate(float deltaTime)
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
