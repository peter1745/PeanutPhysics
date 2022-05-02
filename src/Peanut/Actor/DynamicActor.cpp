#include "DynamicActor.h"
#include "Collision/BoxShape.h"

namespace Peanut {

	DynamicActorImpl::DynamicActorImpl(const Transform& transform)
		: ActorBase(ActorType::Dynamic, transform)
	{
	}

	DynamicActorImpl::DynamicActorImpl(const DynamicActorImpl& other)
		: ActorBase(other)
	{
		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_AngularVelocity = other.m_AngularVelocity;
		m_Force = other.m_Force;
		m_Restitution = other.m_Restitution;
	}

	DynamicActorImpl::DynamicActorImpl(DynamicActorImpl&& other) noexcept
		: ActorBase(std::move(other))
	{
		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_AngularVelocity = other.m_AngularVelocity;
		m_Force = other.m_Force;
		m_Restitution = other.m_Restitution;

		other.m_InverseMass = 0.0f;
		other.m_LinearVelocity = glm::vec3(0.0f);
		other.m_AngularVelocity = glm::vec3(0.0f);
		other.m_Force = glm::vec3(0.0f);
		other.m_Restitution = 0.0f;
	}

	void DynamicActorImpl::UpdateTransform(const float deltaTime)
	{
		// Update location
		m_Transform.Location += m_LinearVelocity * deltaTime;

		// Update angular velocity
		glm::vec3 centerOfMass = GetCenterOfMass();
		glm::vec3 comToLocation = m_Transform.Location - centerOfMass;

		glm::mat3 orientation = glm::toMat3(m_Transform.Orientation);
		glm::mat3 inertiaTensor = orientation * m_Shape->GetInertiaTensor() * glm::transpose(orientation);
		glm::vec3 alpha = glm::inverse(inertiaTensor) * glm::cross(m_AngularVelocity, inertiaTensor * m_AngularVelocity);
		m_AngularVelocity += alpha * deltaTime;

		// Update orientation
		glm::vec3 angularVelocityDelta = m_AngularVelocity * deltaTime;
		glm::quat deltaQuat = glm::quat(glm::length(angularVelocityDelta), angularVelocityDelta);
		m_Transform.Orientation = glm::normalize(deltaQuat * m_Transform.Orientation);

		m_Transform.Location = centerOfMass + glm::rotate(deltaQuat, comToLocation);
	}

	void DynamicActorImpl::ApplyImpulse(const glm::vec3& impulsePoint, const glm::vec3& impulse)
	{
		if (m_InverseMass == 0.0f)
			return;

		ApplyLinearImpulse(impulse);

		glm::vec3 r = impulsePoint - GetCenterOfMass();
		ApplyAngularImpulse(glm::cross(r, impulse));
	}

	void DynamicActorImpl::ApplyLinearImpulse(const glm::vec3& impulse)
	{
		if (m_InverseMass == 0.0f)
			return;

		m_LinearVelocity += impulse * m_InverseMass;
	}

	void DynamicActorImpl::ApplyAngularImpulse(const glm::vec3& impulse)
	{
		if (m_InverseMass == 0.0f)
			return;

		m_AngularVelocity += GetInverseInertiaTensor() * impulse;
		const float maxAngularVelocity = 30.0f; // Radians per second
		if (glm::length2(m_AngularVelocity) > maxAngularVelocity * maxAngularVelocity)
		{
			m_AngularVelocity = glm::normalize(m_AngularVelocity);
			m_AngularVelocity *= maxAngularVelocity;
		}
	}

	void DynamicActorImpl::SetMassAndUpdateInertia(float mass)
	{
		m_InverseMass = mass > 0.0f ? 1.0f / mass : 0.0f;
		
		if (m_Shape)
			m_Shape->CalculateInertiaTensor();
	}

	glm::mat3 DynamicActorImpl::GetInverseInertiaTensor() const
	{
		glm::mat3 inverseInertiaTensor = glm::inverse(m_Shape->GetInertiaTensor()) * m_InverseMass;
		glm::mat3 orientation = glm::toMat3(m_Transform.Orientation);
		return orientation * inverseInertiaTensor * glm::transpose(orientation);
	}

	DynamicActorImpl& DynamicActorImpl::operator=(DynamicActorImpl&& other) noexcept
	{
		ActorBase::operator=(std::move(other));

		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_AngularVelocity = other.m_AngularVelocity;
		m_Force = other.m_Force;
		m_Restitution = other.m_Restitution;

		other.m_InverseMass = 0.0f;
		other.m_LinearVelocity = glm::vec3(0.0f);
		other.m_AngularVelocity = glm::vec3(0.0f);
		other.m_Force = glm::vec3(0.0f);
		other.m_Restitution = 0.0f;
		return *this;
	}

	DynamicActorImpl& DynamicActorImpl::operator=(const DynamicActorImpl& other)
	{
		ActorBase::operator=(other);

		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_AngularVelocity = other.m_AngularVelocity;
		m_Force = other.m_Force;
		m_Restitution = other.m_Restitution;
		return *this;
	}
}
