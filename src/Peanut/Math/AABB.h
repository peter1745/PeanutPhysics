#pragma once

#include <glm/glm.hpp>

namespace Peanut {

	struct AABB
	{
		glm::vec3 Min;
		glm::vec3 Max;

		AABB();
		AABB(const AABB& other);
		AABB(AABB&& other) noexcept;

		AABB(const glm::vec3& center, float radius);
		AABB(const glm::vec3& p1, const glm::vec3& p2);
		~AABB() = default;

		AABB& operator=(const AABB& other);
		AABB& operator=(AABB&& other) noexcept;

		void Invalidate()
		{
			Min = glm::vec3(1.0f);
			Max = glm::vec3(-1.0f);
		}

		bool IsValid() const
		{
			return Min.x < Max.x && Min.y < Max.y && Min.z < Max.z;
		}

		void Extend(float scalar);
		void Extend(const glm::vec3& p);
		void Extend(const glm::vec3& center, float radius);
		void Extend(const AABB& aabb);

		void Translate(const glm::vec3& translation);
		void Scale(const glm::vec3& scale, const glm::vec3& origin);

		glm::vec3 GetCenter() const;
		glm::vec3 GetDiagonal() const;
		
		float GetLongestEdge() const;
		float GetShortestEdge() const;

		bool IsOverlaping(const AABB& aabb) const;

		enum class Intersection { Inside, Intersect, Outside };
		Intersection GetIntersection(const AABB& aabb) const;

		bool IsSimiliar(const AABB& aabb, float diff = 0.5f) const;

	};

}
