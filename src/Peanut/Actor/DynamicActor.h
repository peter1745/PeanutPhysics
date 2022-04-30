#pragma once

#include "ActorBase.h"
#include "Collision/Shape.h"

namespace Peanut {

	class DynamicActorImpl : public ActorBase
	{
	public:
		DynamicActorImpl(const DynamicActorImpl& other);
		DynamicActorImpl(DynamicActorImpl&& other) noexcept;
		DynamicActorImpl& operator=(const DynamicActorImpl& other);
		DynamicActorImpl& operator=(DynamicActorImpl&& other) noexcept;

		const glm::vec3& GetVelocity() const { return m_Velocity; }
		const glm::vec3& GetForce() const { return m_Force; }

		float GetMass() const { return m_Mass; }
		void SetMass(float mass) { m_Mass = mass; }

	private:
		DynamicActorImpl(const Transform& transform);

	private:
		float m_Mass = 1.0f;
		glm::vec3 m_Velocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Force = { 0.0f, 0.0f, 0.0f };

		friend class PeanutSDK;
		friend class PhysicsWorldImpl;
	};

	using DynamicActor = SharedPtr<DynamicActorImpl>;

}
