#pragma once

#include "ShapeBase.h"

namespace Peanut {

	class SphereShapeImpl : public ShapeBaseImpl
	{
	public:
		SphereShapeImpl(const float radius);

		virtual void CalculateInertiaTensor() override;
		float GetRadius() const { return m_Radius; }

	private:
		float m_Radius;
	};

	using SphereShape = Ref<SphereShapeImpl>;

}
