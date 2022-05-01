#include "DynamicActor.h"

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
		m_Force = other.m_Force;
	}

	DynamicActorImpl::DynamicActorImpl(DynamicActorImpl&& other) noexcept
		: ActorBase(std::move(other))
	{
		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_Force = other.m_Force;

		other.m_InverseMass = 0.0f;
		other.m_LinearVelocity = glm::vec3(0.0f);
		other.m_Force = glm::vec3(0.0f);
	}

	void DynamicActorImpl::ApplyLinearImpulse(const glm::vec3& impulse)
	{
		if (m_InverseMass == 0.0f)
			return;

		m_LinearVelocity += impulse * m_InverseMass;
	}

	DynamicActorImpl& DynamicActorImpl::operator=(DynamicActorImpl&& other) noexcept
	{
		ActorBase::operator=(std::move(other));

		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_Force = other.m_Force;

		other.m_InverseMass = 0.0f;
		other.m_LinearVelocity = glm::vec3(0.0f);
		other.m_Force = glm::vec3(0.0f);
		return *this;
	}

	DynamicActorImpl& DynamicActorImpl::operator=(const DynamicActorImpl& other)
	{
		ActorBase::operator=(other);

		m_InverseMass = other.m_InverseMass;
		m_LinearVelocity = other.m_LinearVelocity;
		m_Force = other.m_Force;
		return *this;
	}
}
