#pragma once

#include "Actor/DynamicActor.h"

#include <vector>

namespace Peanut {

	struct Contact
	{
		glm::vec3 WorldSpacePoint0;
		glm::vec3 WorldSpacePoint1;
		glm::vec3 LocalSpacePoint0;
		glm::vec3 LocalSpacePoint1;

		glm::vec3 Normal;
		float Distance;
		float ImpactTime;

		Ref<ActorBase> Actor0;
		Ref<ActorBase> Actor1;
	};

	class PhysicsWorldImpl : public RefCounted
	{
	private:
		PhysicsWorldImpl(const glm::vec3& gravity);

	public:
		~PhysicsWorldImpl();

		void AddActor(const DynamicActor& actor);
		void RemoveActor(const DynamicActor& actor);

		void Simulate(float deltaTime);

	private:
		void ResolveContact(const Contact& contact) const;
		bool Intersect(const Ref<ActorBase>& actor0, const Ref<ActorBase>& actor1, Contact& outContact) const;

	private:
		std::vector<DynamicActor> m_DynamicActors;
		glm::vec3 m_Gravity = { 0.0f, -9.81f, 0.0f };

		friend class PeanutSDKImpl;
	};

	using PhysicsWorld = Ref<PhysicsWorldImpl>;
}
