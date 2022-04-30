#include "Shape.h"

namespace Peanut {

	ShapeImpl::ShapeImpl(const SharedPtr<GeometryBase>& geometry)
		: m_Geometry(geometry)
	{
		ComputeBoundingBox();
	}

	ShapeImpl::ShapeImpl(const ShapeImpl& other)
		: m_Geometry(other.m_Geometry), m_BoundingBox(other.m_BoundingBox)
	{
	}

	ShapeImpl::ShapeImpl(ShapeImpl&& other) noexcept
	{
		m_Geometry = std::move(other.m_Geometry);
		m_BoundingBox = std::move(other.m_BoundingBox);
	}

	void ShapeImpl::ComputeBoundingBox()
	{
		switch (m_Geometry->GetType())
		{
			case GeometryType::Box:
			{
				SharedPtr<BoxGeometry> boxGeometry = std::dynamic_pointer_cast<BoxGeometry>(m_Geometry);
				glm::vec3 minBound = m_LocalTransform.Location - boxGeometry->HalfExtents;
				glm::vec3 maxBound = m_LocalTransform.Location + boxGeometry->HalfExtents;
				m_BoundingBox = AABB(minBound, maxBound);
				break;
			}
			case GeometryType::Sphere:
				break;
			case GeometryType::Capsule:
				break;
		}
	}

	ShapeImpl& ShapeImpl::operator=(ShapeImpl&& other) noexcept
	{
		m_Geometry = std::move(other.m_Geometry);
		m_BoundingBox = std::move(other.m_BoundingBox);
		return *this;
	}

	ShapeImpl& ShapeImpl::operator=(const ShapeImpl& other)
	{
		m_Geometry = other.m_Geometry;
		m_BoundingBox = other.m_BoundingBox;
		return *this;
	}

}
