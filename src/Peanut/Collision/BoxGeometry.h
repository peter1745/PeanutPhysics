#pragma once

#include "GeometryBase.h"

namespace Peanut {

	struct BoxGeometry : public GeometryBase
	{
		glm::vec3 HalfExtents;

		virtual GeometryType GetType() const override { return GeometryType::Box; }
	};

}
