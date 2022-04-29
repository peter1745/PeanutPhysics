#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <memory>
#include <utility>

namespace Peanut {

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;

	template<typename T, typename... TArgs>
	SharedPtr<T> MakeShared(TArgs&&... args)
	{
		return std::make_shared<T>(std::forward<TArgs>(args)...);
	}

}
