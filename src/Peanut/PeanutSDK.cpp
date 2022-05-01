#include "PeanutSDK.h"

namespace Peanut {

	static bool s_SDKCreated = false;

	PhysicsWorld PeanutSDKImpl::CreateWorld(const glm::vec3& gravity)
	{
		return PhysicsWorld(new PhysicsWorldImpl(gravity));
	}

	DynamicActor PeanutSDKImpl::CreateDynamicActor(const Transform& initialTransform)
	{
		return DynamicActor(new DynamicActorImpl(initialTransform));
	}

	BoxShape PeanutSDKImpl::CreateBoxShape(const glm::vec3& halfExtents)
	{
		return BoxShape(new BoxShapeImpl(halfExtents));
	}

	Ref<PeanutSDKImpl> CreateSDK()
	{
		if (s_SDKCreated)
		{
			// TODO: Log error
			return nullptr;
		}

		s_SDKCreated = true;
		return PeanutSDK::Create();
	}
}
