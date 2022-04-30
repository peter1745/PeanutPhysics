#pragma once

#include "PhysicsWorld.h"
#include "Actor/DynamicActor.h"
#include "Collision/BoxGeometry.h"

namespace Peanut {

	class PeanutSDK
	{
	public:
		void Release();

		PhysicsWorld CreateWorld(const glm::vec3& gravity = glm::vec3(0.0f, -9.81f, 0.0f));
		DynamicActor CreateDynamicActor(const Transform& initialTransform);
		Shape CreateShape(const BoxGeometry& geometry);

	public:
		static SharedPtr<PeanutSDK> CreateSDK();
		static SharedPtr<PeanutSDK> Get() { return s_Instance; }

	private:
		PeanutSDK();

	private:
		static SharedPtr<PeanutSDK> s_Instance;
	};

}
