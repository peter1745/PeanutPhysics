#include "BoxShape.h"

namespace Peanut {

	BoxShapeImpl::BoxShapeImpl(const glm::vec3& halfExtents)
		: ShapeBaseImpl(ShapeType::Box), m_HalfExtents(halfExtents)
	{
		glm::vec3 minBound = m_LocalTransform.Location - m_HalfExtents;
		glm::vec3 maxBound = m_LocalTransform.Location + m_HalfExtents;
		m_BoundingBox = AABB(minBound, maxBound);
	}

	BoxShapeImpl::BoxShapeImpl(BoxShapeImpl&& other) noexcept
		: ShapeBaseImpl(std::move(other))
	{
		m_HalfExtents = other.m_HalfExtents;
		other.m_HalfExtents = glm::vec3(0.0f);
	}

	BoxShapeImpl::BoxShapeImpl(const BoxShapeImpl& other)
		: ShapeBaseImpl(other)
	{
		m_HalfExtents = other.m_HalfExtents;
	}

	BoxShapeImpl& BoxShapeImpl::operator=(const BoxShapeImpl& other)
	{
		ShapeBaseImpl::operator=(other);
		m_HalfExtents = other.m_HalfExtents;

		return *this;
	}

	BoxShapeImpl& BoxShapeImpl::operator=(BoxShapeImpl&& other) noexcept
	{
		ShapeBaseImpl::operator=(std::move(other));
		m_HalfExtents = other.m_HalfExtents;
		other.m_HalfExtents = glm::vec3(0.0f);

		return *this;
	}

}
