#include "SphereShape.h"

namespace Peanut {

	SphereShapeImpl::SphereShapeImpl(const float radius)
		: ShapeBaseImpl(ShapeType::Sphere), m_Radius(radius)
	{
		m_BoundingBox = AABB(m_LocalTransform.Location, radius);
	}

	void SphereShapeImpl::CalculateInertiaTensor()
	{
		m_InertiaTensor = glm::mat3(0.0f);

		const float t = 2.0f * m_Radius * m_Radius / 5.0f;
		m_InertiaTensor[0] = glm::vec3(t, 0.0f, 0.0f);
		m_InertiaTensor[1] = glm::vec3(0.0f, t, 0.0f);
		m_InertiaTensor[2] = glm::vec3(0.0f, 0.0f, t);
	}

}
