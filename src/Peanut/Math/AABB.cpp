#include "AABB.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>

namespace Peanut {

	AABB::AABB()
	{
		Invalidate();
	}

	AABB::AABB(const AABB& other)
	{
		Min = other.Min;
		Max = other.Max;
	}

	AABB::AABB(AABB&& other) noexcept
	{
		Min = other.Min;
		Max = other.Max;
		other.Invalidate();
	}

	AABB& AABB::operator=(AABB&& other) noexcept
	{
		Min = other.Min;
		Max = other.Max;
		other.Invalidate();
		return *this;
	}

	AABB& AABB::operator=(const AABB& other)
	{
		Min = other.Min;
		Max = other.Max;
		return *this;
	}

	AABB::AABB(const glm::vec3& center, float radius)
	{
		Invalidate();
		Extend(center, radius);
	}

	AABB::AABB(const glm::vec3& p1, const glm::vec3& p2)
	{
		Invalidate();
		Min = p1;
		Max = p2;
	}

	void AABB::Extend(float scalar)
	{
		if (IsValid())
		{
			Min -= scalar;
			Max += scalar;
		}
	}

	void AABB::Extend(const glm::vec3& p)
	{
		if (IsValid())
		{
			Min = glm::min(p, Min);
			Max = glm::max(p, Max);
		}
		else
		{
			Min = p;
			Max = p;
		}
	}

	void AABB::Extend(const glm::vec3& center, float radius)
	{
		if (IsValid())
		{
			Min = glm::min(center - radius, Min);
			Max = glm::max(center + radius, Max);
		}
		else
		{
			Min = center - radius;
			Max = center + radius;
		}
	}

	void AABB::Extend(const AABB& aabb)
	{
		if (aabb.IsValid())
		{
			Extend(aabb.Min);
			Extend(aabb.Max);
		}
	}

	void AABB::Translate(const glm::vec3& translation)
	{
		if (IsValid())
		{
			Min += translation;
			Max += translation;
		}
	}

	void AABB::Scale(const glm::vec3& scale, const glm::vec3& origin)
	{
		if (IsValid())
		{
			Min = (Min - origin) * scale + origin;
			Max = (Max - origin) * scale + origin;
		}
	}

	glm::vec3 AABB::GetCenter() const
	{
		return IsValid() ? Min + (GetDiagonal() * 0.5f) : glm::vec3(0.0f);
	}

	glm::vec3 AABB::GetDiagonal() const
	{
		return IsValid() ? Max - Min : glm::vec3(0.0f);
	}

	float AABB::GetLongestEdge() const
	{
		return glm::compMax(GetDiagonal());
	}

	float AABB::GetShortestEdge() const
	{
		return glm::compMin(GetDiagonal());
	}

	bool AABB::IsOverlaping(const AABB& aabb) const
	{
		if (!IsValid() || !aabb.IsValid())
			return false;

		float ax = aabb.Min.x - Max.x;
		float ay = aabb.Min.y - Max.y;
		float az = aabb.Min.z - Max.z;
		float bx = Min.x - aabb.Max.x;
		float by = Min.y - aabb.Max.y;
		float bz = Min.z - aabb.Max.z;

		if (ax > 0.0f || ay > 0.0f || az > 0.0f)
			return false;

		if (bx > 0.0f || by > 0.0f || bz > 0.0f)
			return false;

		return true;
	}

	AABB::Intersection AABB::GetIntersection(const AABB& aabb) const
	{
		if (!IsValid() || !aabb.IsValid())
			return AABB::Intersection::Outside;

		if (Max.x < aabb.Min.x || Min.x > aabb.Max.x ||
			Max.y < aabb.Min.y || Min.y > aabb.Max.y ||
			Max.z < aabb.Min.z || Min.z > aabb.Max.z)
		{
			return AABB::Intersection::Outside;
		}

		if (Min.x <= aabb.Min.x && Max.x >= aabb.Max.x &&
			Min.y <= aabb.Min.y && Max.y >= aabb.Max.y &&
			Min.z <= aabb.Min.z && Max.z >= aabb.Max.z)
		{
			return AABB::Intersection::Inside;
		}

		return AABB::Intersection::Intersect;
	}

	bool AABB::IsSimiliar(const AABB& aabb, float diff) const
	{
		if (!IsValid() || !aabb.IsValid())
			return false;

		glm::vec3 acceptableDiff = ((GetDiagonal() + aabb.GetDiagonal()) / 2.0f) * diff;
		glm::vec3 minDiff = glm::abs(Min - aabb.Min);

		if (minDiff.x > acceptableDiff.x || minDiff.y > acceptableDiff.y || minDiff.z > acceptableDiff.z)
			return false;

		glm::vec3 maxDiff = glm::abs(Max - aabb.Max);

		if (maxDiff.x > acceptableDiff.x || maxDiff.y > acceptableDiff.y || maxDiff.z > acceptableDiff.z)
			return false;

		return true;
	}

}
