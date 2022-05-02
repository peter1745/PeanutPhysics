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

	void BoxShapeImpl::CalculateInertiaTensor()
	{
		float volume = 1.0f;
		if (m_HalfExtents.x != 0.0f) volume *= m_HalfExtents.x;
		if (m_HalfExtents.y != 0.0f) volume *= m_HalfExtents.y;
		if (m_HalfExtents.z != 0.0f) volume *= m_HalfExtents.z;

		const float m = 8.0f * volume;
		const float s = (1.0f / 3.0f) * m;

		const float x = m_HalfExtents.x * m_HalfExtents.x;
		const float y = m_HalfExtents.y * m_HalfExtents.y;
		const float z = m_HalfExtents.z * m_HalfExtents.z;

		m_InertiaTensor[0] = glm::vec3(y + z, 0.0f, 0.0f);
		m_InertiaTensor[1] = glm::vec3(0.0f, z + x, 0.0f);
		m_InertiaTensor[2] = glm::vec3(0.0f, 0.0f, x + y);
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
