#pragma once

#include "Common.h"

namespace Peanut {

	struct Transform
	{
		glm::vec3 Location;
		glm::quat Orientation;

		Transform() { SetIdentity(); }
		Transform(const glm::vec3& location, const glm::quat& orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
		{
			Location = location;
			Orientation = orientation;
		}

		void SetIdentity()
		{
			Location = glm::vec3(0.0f);
			Orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		}

	};

}
