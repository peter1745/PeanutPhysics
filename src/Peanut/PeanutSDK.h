#pragma once

#include "PhysicsWorld.h"
#include "Actor/DynamicActor.h"
#include "Collision/BoxShape.h"
#include "Collision/SphereShape.h"

namespace Peanut {

	class PeanutSDKImpl : public RefCounted
	{
	public:
		PhysicsWorld CreateWorld(const glm::vec3& gravity = glm::vec3(0.0f, -9.81f, 0.0f));
		DynamicActor CreateDynamicActor(const Transform& initialTransform);
		BoxShape CreateBoxShape(const glm::vec3& halfExtents);
		SphereShape CreateSphereShape(const float radius);
	};

	Ref<PeanutSDKImpl> CreateSDK();

	using PeanutSDK = Ref<PeanutSDKImpl>;

}
