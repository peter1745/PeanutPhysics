#pragma once

#include "GeometryBase.h"

namespace Peanut {

	struct BoxGeometry : public GeometryBase
	{
		glm::vec3 HalfExtents;

		BoxGeometry(const glm::vec3& halfExtents)
			: HalfExtents(halfExtents) {}

		BoxGeometry(float halfWidth, float halfHeight, float halfDepth)
			: HalfExtents({ halfWidth, halfHeight, halfDepth }) {}

		virtual GeometryType GetType() const override { return GeometryType::Box; }
	};

}
