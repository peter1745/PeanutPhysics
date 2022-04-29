#include "DynamicActor.h"

namespace Peanut {

	DynamicActorImpl::DynamicActorImpl(const Transform& transform)
		: ActorBase(ActorType::Dynamic, transform)
	{
	}

	DynamicActorImpl::DynamicActorImpl(const DynamicActorImpl& other)
		: ActorBase(other)
	{
		m_Mass = other.m_Mass;
		m_Velocity = other.m_Velocity;
		m_Force = other.m_Force;
	}

	DynamicActorImpl::DynamicActorImpl(DynamicActorImpl&& other) noexcept
		: ActorBase(std::move(other))
	{
		m_Mass = other.m_Mass;
		m_Velocity = other.m_Velocity;
		m_Force = other.m_Force;

		other.m_Mass = 0.0f;
		other.m_Velocity = glm::vec3(0.0f);
		other.m_Force = glm::vec3(0.0f);
	}

	DynamicActorImpl& DynamicActorImpl::operator=(DynamicActorImpl&& other) noexcept
	{
		ActorBase::operator=(std::move(other));

		m_Mass = other.m_Mass;
		m_Velocity = other.m_Velocity;
		m_Force = other.m_Force;

		other.m_Mass = 0.0f;
		other.m_Velocity = glm::vec3(0.0f);
		other.m_Force = glm::vec3(0.0f);
		return *this;
	}

	DynamicActorImpl& DynamicActorImpl::operator=(const DynamicActorImpl& other)
	{
		ActorBase::operator=(other);

		m_Mass = other.m_Mass;
		m_Velocity = other.m_Velocity;
		m_Force = other.m_Force;
		return *this;
	}
}
