#pragma once

#include "GeometryBase.h"
#include "Common/Transform.h"

namespace Peanut {

	class Shape
	{
	public:
		Shape(const Shape& other);
		Shape(Shape&& other) noexcept;
		Shape& operator=(const Shape& other);
		Shape& operator=(Shape&& other) noexcept;

	public:
		void SetLocalTransform(const Transform& localTransform) { m_LocalTransform = localTransform; }
		const Transform& GetLocalTransform() const { return m_LocalTransform; }

		void SetGeometry(const SharedPtr<GeometryBase>& geometry) { m_Geometry = geometry; }
		const SharedPtr<GeometryBase>& GetGeometry() const { return m_Geometry; }

	private:
		Shape(const SharedPtr<GeometryBase>& geometry);

	private:
		Transform m_LocalTransform;
		SharedPtr<GeometryBase> m_Geometry = nullptr;
	};

}
