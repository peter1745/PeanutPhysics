#include "ShapeBase.h"

namespace Peanut {

	ShapeBaseImpl::ShapeBaseImpl(const ShapeBaseImpl& other)
		: m_Type(other.m_Type), m_LocalTransform(other.m_LocalTransform), m_BoundingBox(other.m_BoundingBox)
	{
	}

	ShapeBaseImpl::ShapeBaseImpl(ShapeBaseImpl&& other) noexcept
	{
		m_Type = other.m_Type;
		m_LocalTransform = std::move(other.m_LocalTransform);
		m_BoundingBox = std::move(other.m_BoundingBox);
		m_CenterOfMass = other.m_CenterOfMass;

		other.m_Type = ShapeType::None;
		other.m_CenterOfMass = glm::vec3(0.0f);
	}

	ShapeBaseImpl& ShapeBaseImpl::operator=(ShapeBaseImpl&& other) noexcept
	{
		m_Type = other.m_Type;
		m_LocalTransform = std::move(other.m_LocalTransform);
		m_BoundingBox = std::move(other.m_BoundingBox);
		m_CenterOfMass = other.m_CenterOfMass;

		other.m_Type = ShapeType::None;
		other.m_CenterOfMass = glm::vec3(0.0f);

		return *this;
	}

	ShapeBaseImpl& ShapeBaseImpl::operator=(const ShapeBaseImpl& other)
	{
		m_Type = other.m_Type;
		m_LocalTransform = other.m_LocalTransform;
		m_BoundingBox = other.m_BoundingBox;
		m_CenterOfMass = other.m_CenterOfMass;
		return *this;
	}

}
