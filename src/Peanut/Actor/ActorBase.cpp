#include "ActorBase.h"

namespace Peanut {

	ActorBase::ActorBase(ActorType type, const Transform& spawnTransform)
		: m_Type(type), m_Transform(spawnTransform)
	{
	}

	ActorBase::ActorBase(const ActorBase& other)
		: m_Type(other.m_Type), m_Transform(other.m_Transform)
	{
	}

	ActorBase::ActorBase(ActorBase&& other) noexcept
	{
		m_Type = other.m_Type;
		m_Transform = other.m_Transform;

		other.m_Type = ActorType::None;
		other.m_Transform.SetIdentity();
	}

	ActorBase::~ActorBase()
	{
		m_Shape = nullptr;
		//m_Shapes.clear();
	}

	ActorBase& ActorBase::operator=(const ActorBase& other)
	{
		m_Type = other.m_Type;
		m_Transform = other.m_Transform;
		return *this;
	}

	ActorBase& ActorBase::operator=(ActorBase&& other) noexcept
	{
		m_Type = other.m_Type;
		m_Transform = other.m_Transform;

		other.m_Type = ActorType::None;
		other.m_Transform.SetIdentity();
		return *this;
	}

	void ActorBase::AttachShape(const Ref<ShapeBaseImpl>& shape)
	{
		//auto found = std::find(m_Shapes.begin(), m_Shapes.end(), shape);

		//if (found != m_Shapes.end())
		//{
		//	// TODO(Peter): Log error!
		//	return;
		//}

		//m_Shapes.push_back(shape);
		m_Shape = shape;
	}

	void ActorBase::DetachShape(const Ref<ShapeBaseImpl>& shape)
	{
		//auto found = std::find(m_Shapes.begin(), m_Shapes.end(), shape);

		//if (found == m_Shapes.end())
		//{
		//	// TODO(Peter): Log error!
		//	return;
		//}

		//m_Shapes.erase(found);
		m_Shape = nullptr;
	}

	glm::vec3 ActorBase::WorldSpaceToActorSpace(const glm::vec3& worldPoint) const
	{
		glm::quat inverseOrientation = glm::inverse(m_Transform.Orientation);
		return glm::rotate(inverseOrientation, worldPoint - GetCenterOfMass());
	}

	glm::vec3 ActorBase::ActorSpaceToWorldSpace(const glm::vec3& worldPoint) const
	{
		return GetCenterOfMass() + glm::rotate(m_Transform.Orientation, worldPoint);
	}

	glm::vec3 ActorBase::GetCenterOfMass() const
	{
		return m_Transform.Location + glm::rotate(m_Transform.Orientation, m_Shape->GetCenterOfMass());
	}

}
