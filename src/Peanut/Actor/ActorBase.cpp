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

	ActorBase::~ActorBase()
	{
		m_Shapes.clear();
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

	void ActorBase::AttachShape(const Shape& shape)
	{
		auto found = std::find(m_Shapes.begin(), m_Shapes.end(), shape);

		if (found != m_Shapes.end())
		{
			// TODO(Peter): Log error!
			return;
		}

		m_Shapes.push_back(shape);
	}

	Shape ActorBase::FindShapeOfType(GeometryType shapeType) const
	{
		for (const auto& shape : m_Shapes)
		{
			if (shape->GetGeometry()->GetType() == shapeType)
				return shape;
		}

		return nullptr;
	}

	void ActorBase::DetachShape(const Shape& shape)
	{
		auto found = std::find(m_Shapes.begin(), m_Shapes.end(), shape);

		if (found == m_Shapes.end())
		{
			// TODO(Peter): Log error!
			return;
		}

		m_Shapes.erase(found);
	}

}
