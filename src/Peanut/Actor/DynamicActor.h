#pragma once

#include "ActorBase.h"
#include "Collision/ShapeBase.h"

namespace Peanut {

	class DynamicActorImpl : public ActorBase
	{
	public:
		DynamicActorImpl(const DynamicActorImpl& other);
		DynamicActorImpl(DynamicActorImpl&& other) noexcept;
		DynamicActorImpl& operator=(const DynamicActorImpl& other);
		DynamicActorImpl& operator=(DynamicActorImpl&& other) noexcept;

		void ApplyLinearImpulse(const glm::vec3& impulse);

		const glm::vec3& GetLinearVelocity() const { return m_LinearVelocity; }
		const glm::vec3& GetForce() const { return m_Force; }

		float GetMass() const { return 1.0f / m_InverseMass; }
		void SetMass(float mass) { m_InverseMass = mass > 0.0f ? 1.0f / mass : 0.0f; }

		bool IsGravityDisabled() const { return m_DisableGravity; }
		void SetGravityDisabled(bool disable) { m_DisableGravity = disable; }

	private:
		DynamicActorImpl(const Transform& transform);

	private:
		float m_InverseMass = 0.0f;
		glm::vec3 m_LinearVelocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Force = { 0.0f, 0.0f, 0.0f };

		bool m_DisableGravity = false;

		friend class PeanutSDKImpl;
		friend class PhysicsWorldImpl;
	};

	using DynamicActor = Ref<DynamicActorImpl>;

}
