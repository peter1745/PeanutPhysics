#pragma once

#include "BoxGeometry.h"
#include "Common/Transform.h"
#include "Math/AABB.h"

namespace Peanut {

	class ShapeImpl
	{
	public:
		ShapeImpl(const ShapeImpl& other);
		ShapeImpl(ShapeImpl&& other) noexcept;
		ShapeImpl& operator=(const ShapeImpl& other);
		ShapeImpl& operator=(ShapeImpl&& other) noexcept;

	public:
		const Transform& GetLocalTransform() const { return m_LocalTransform; }
		void SetLocalTransform(const Transform& localTransform)
		{
			m_BoundingBox.Translate(localTransform.Location - m_LocalTransform.Location);
			m_LocalTransform = localTransform;
		}

		const SharedPtr<GeometryBase>& GetGeometry() const { return m_Geometry; }
		void SetGeometry(const SharedPtr<GeometryBase>& geometry)
		{
			m_Geometry = geometry;
		}

		const AABB& GetBoundingBox() const { return m_BoundingBox; }

	private:
		void ComputeBoundingBox();

	private:
		ShapeImpl(const SharedPtr<GeometryBase>& geometry);

	private:
		Transform m_LocalTransform;
		SharedPtr<GeometryBase> m_Geometry = nullptr;
		AABB m_BoundingBox;

		friend class PeanutSDK;
		friend class ActorBase;
	};

	using Shape = SharedPtr<ShapeImpl>;

}
