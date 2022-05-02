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

		void ApplyImpulse(const glm::vec3& impulsePoint, const glm::vec3& impulse);
		void ApplyLinearImpulse(const glm::vec3& impulse);
		void ApplyAngularImpulse(const glm::vec3& impulse);

		const glm::vec3& GetLinearVelocity() const { return m_LinearVelocity; }
		const glm::vec3& GetAngularVelocity() const { return m_AngularVelocity; }
		const glm::vec3& GetForce() const { return m_Force; }

		float GetMass() const { return 1.0f / m_InverseMass; }
		void SetMass(float mass) { m_InverseMass = mass > 0.0f ? 1.0f / mass : 0.0f; }

		bool IsGravityDisabled() const { return m_DisableGravity || m_InverseMass == 0.0f; }
		void SetGravityDisabled(bool disable) { m_DisableGravity = disable; }

		float GetRestitution() const { return m_Restitution; }
		void SetRestitution(float restiution) { m_Restitution = glm::clamp(restiution, 0.0f, 1.0f); }

		glm::vec3 GetCenterOfMass() const { return m_Transform.Location + glm::rotate(m_Transform.Orientation, m_Shape->GetCenterOfMass()); }
		glm::vec3 GetLocalCenterOfMass() const { return m_Shape->GetCenterOfMass(); }

		void SetMassAndUpdateInertia(float mass);
		const glm::mat3& GetInertiaTensor() const { return m_Shape->GetInertiaTensor(); }
		glm::mat3 GetInverseInertiaTensor() const;
		glm::mat3 GetLocalInverseInertiaTensor() const { return glm::inverse(m_Shape->GetInertiaTensor()) * m_InverseMass; }

	private:
		DynamicActorImpl(const Transform& transform);

		void UpdateTransform(const float deltaTime);

	private:
		float m_InverseMass = 0.0f;
		glm::vec3 m_LinearVelocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_AngularVelocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Force = { 0.0f, 0.0f, 0.0f };
		float m_Restitution = 0.5f;

		bool m_DisableGravity = false;

		friend class PeanutSDKImpl;
		friend class PhysicsWorldImpl;
	};

	using DynamicActor = Ref<DynamicActorImpl>;

}
