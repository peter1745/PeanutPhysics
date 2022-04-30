#include "PeanutSDK.h"

namespace Peanut {

	PeanutSDK::PeanutSDK()
	{

	}

	void PeanutSDK::Release()
	{
		if (this != s_Instance.get())
		{
			// TODO(Peter): Log error!
			__debugbreak();
		}

		s_Instance.reset();
	}

	PhysicsWorld PeanutSDK::CreateWorld(const glm::vec3& gravity)
	{
		return MakeShared<PhysicsWorldImpl>(new PhysicsWorldImpl(gravity));
	}

	DynamicActor PeanutSDK::CreateDynamicActor(const Transform& initialTransform)
	{
		return MakeShared<DynamicActorImpl>(new DynamicActorImpl(initialTransform));
	}

	Shape PeanutSDK::CreateShape(const BoxGeometry& geometry)
	{
		return MakeShared<ShapeImpl>(new ShapeImpl(MakeShared<BoxGeometry>(geometry)));
	}

	SharedPtr<PeanutSDK> PeanutSDK::CreateSDK()
	{
		if (s_Instance)
		{
			// TODO(Peter): Log Error!
			return nullptr;
		}

		SharedPtr<PeanutSDK> sdk = MakeShared<PeanutSDK>(new PeanutSDK());
		s_Instance = sdk;
		return sdk;
	}

	SharedPtr<PeanutSDK> PeanutSDK::s_Instance;

}
