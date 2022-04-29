#pragma once

#include "Common/Common.h"

namespace Peanut {

	// TODO(Peter): Mesh colliders!
	enum class GeometryType : int8_t
	{
		None = -1, Box, Sphere, Capsule
	};

	struct GeometryBase
	{
		virtual GeometryType GetType() const = 0;
	};

}
