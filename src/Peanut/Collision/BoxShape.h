#pragma once

#include "ShapeBase.h"

namespace Peanut {

	class BoxShapeImpl : public ShapeBaseImpl
	{
	public:
		BoxShapeImpl(const glm::vec3& halfExtents);

		BoxShapeImpl(float halfWidth, float halfHeight, float halfDepth)
			: BoxShapeImpl(glm::vec3(halfWidth, halfHeight, halfDepth))
		{
		}

		BoxShapeImpl(BoxShapeImpl&& other) noexcept;
		BoxShapeImpl(const BoxShapeImpl& other);
		BoxShapeImpl& operator=(BoxShapeImpl&& other) noexcept;
		BoxShapeImpl& operator=(const BoxShapeImpl& other);

		virtual void CalculateInertiaTensor() override;

		const glm::vec3& GetHalfExtents() const { return m_HalfExtents; }

	private:
		glm::vec3 m_HalfExtents;
	};

	using BoxShape = Ref<BoxShapeImpl>;

}
