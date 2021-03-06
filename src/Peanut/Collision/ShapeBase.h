#pragma once

#include "Common/Ref.h"
#include "Common/Transform.h"
#include "Math/AABB.h"

namespace Peanut {

	enum class ShapeType
	{
		None = -1, Box, Sphere, Capsule
	};

	class ShapeBaseImpl : public RefCounted
	{
	protected:
		ShapeBaseImpl(ShapeType type)
			: m_Type(type), m_CenterOfMass(glm::vec3(0.0f)) {}

	public:
		ShapeBaseImpl(const ShapeBaseImpl& other);
		ShapeBaseImpl(ShapeBaseImpl&& other) noexcept;
		ShapeBaseImpl& operator=(const ShapeBaseImpl& other);
		ShapeBaseImpl& operator=(ShapeBaseImpl&& other) noexcept;

		ShapeType GetType() const { return m_Type; }

		const Transform& GetLocalTransform() const { return m_LocalTransform; }
		void SetLocalTransform(const Transform& localTransform)
		{
			m_BoundingBox.Translate(localTransform.Location - m_LocalTransform.Location);
			m_LocalTransform = localTransform;
		}

		const AABB& GetBoundingBox() const { return m_BoundingBox; }
		const glm::vec3& GetCenterOfMass() const { return m_CenterOfMass; }

		const glm::mat3& GetInertiaTensor() const { return m_InertiaTensor; }

	private:
		virtual void CalculateInertiaTensor() = 0;

	private:
		ShapeType m_Type;

	protected:
		Transform m_LocalTransform;
		AABB m_BoundingBox;
		glm::vec3 m_CenterOfMass = glm::vec3(0.0f);
		glm::mat3 m_InertiaTensor = glm::mat3(0.0f);

		friend class PeanutSDKImpl;
		friend class ActorBase;
		friend class DynamicActorImpl;
	};

	using ShapeBase = Ref<ShapeBaseImpl>;

}
