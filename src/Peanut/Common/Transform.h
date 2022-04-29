#pragma once

#include "Common.h"

namespace Peanut {

	struct Transform
	{
		glm::vec3 Location;
		glm::quat Rotation;

		Transform() { SetIdentity(); }
		Transform(const glm::vec3& location, const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
		{
			Location = location;
			Rotation = rotation;
		}

		void SetIdentity()
		{
			Location = glm::vec3(0.0f);
			Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		}

	};

}
