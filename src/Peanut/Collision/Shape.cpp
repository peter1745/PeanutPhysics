#include "Shape.h"

namespace Peanut {

	Shape::Shape(const SharedPtr<GeometryBase>& geometry)
		: m_Geometry(geometry)
	{
	}

	Shape::Shape(const Shape& other)
		: m_Geometry(other.m_Geometry)
	{
	}

	Shape::Shape(Shape&& other) noexcept
	{
		m_Geometry = std::move(other.m_Geometry);
	}

	Shape& Shape::operator=(Shape&& other) noexcept
	{
		m_Geometry = std::move(other.m_Geometry);
		return *this;
	}

	Shape& Shape::operator=(const Shape& other)
	{
		m_Geometry = other.m_Geometry;
		return *this;
	}

}
