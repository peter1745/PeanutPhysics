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

		other.m_Type = ShapeType::None;
	}

	ShapeBaseImpl& ShapeBaseImpl::operator=(ShapeBaseImpl&& other) noexcept
	{
		m_Type = other.m_Type;
		m_LocalTransform = std::move(other.m_LocalTransform);
		m_BoundingBox = std::move(other.m_BoundingBox);
		other.m_Type = ShapeType::None;

		return *this;
	}

	ShapeBaseImpl& ShapeBaseImpl::operator=(const ShapeBaseImpl& other)
	{
		m_Type = other.m_Type;
		m_LocalTransform = other.m_LocalTransform;
		m_BoundingBox = other.m_BoundingBox;
		return *this;
	}

}
