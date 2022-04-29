#include "ActorBase.h"

namespace Peanut {

	ActorBase::ActorBase(ActorType type, const Transform& spawnTransform)
		: m_Type(type), m_Transform(spawnTransform)
	{
	}

	ActorBase::ActorBase(const ActorBase& other)
		: m_ActorID(other.m_ActorID), m_Type(other.m_Type), m_Transform(other.m_Transform)
	{
	}

	ActorBase::ActorBase(ActorBase&& other) noexcept
	{
		m_ActorID = other.m_ActorID;
		m_Type = other.m_Type;
		m_Transform = other.m_Transform;

		other.m_ActorID = 0;
		other.m_Type = ActorType::None;
		other.m_Transform.SetIdentity();
	}

	ActorBase& ActorBase::operator=(const ActorBase& other)
	{
		m_ActorID = other.m_ActorID;
		m_Type = other.m_Type;
		m_Transform = other.m_Transform;
		return *this;
	}

	ActorBase& ActorBase::operator=(ActorBase&& other) noexcept
	{
		m_ActorID = other.m_ActorID;
		m_Type = other.m_Type;
		m_Transform = other.m_Transform;

		other.m_ActorID = 0;
		other.m_Type = ActorType::None;
		other.m_Transform.SetIdentity();
		return *this;
	}

}
