#pragma once

#include "Actor/DynamicActor.h"

#include <vector>

namespace Peanut {

	class PhysicsWorld
	{
	public:
		DynamicActor CreateDynamicActor(const Transform& initialTransform);
		void RemoveActor(const DynamicActor& actor);

		void Simulate(float deltaTime);

	private:
		// NOTE(Peter): Not the same Ref as Hazel! This is just a using of std::shared_ptr for now...
		std::vector<DynamicActor> m_DynamicActors;
		uint32_t m_NextActorID = 0;
		glm::vec3 m_Gravity = { 0.0f, -9.81f, 0.0f };
	};

}
