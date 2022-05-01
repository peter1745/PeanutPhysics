#pragma once

#include "Common/Ref.h"
#include "Collision/ShapeBase.h"

#include <vector>

namespace Peanut {

	enum class ActorType : int8_t
	{
		None = -1, Static, Dynamic
	};

	class ActorBase : public RefCounted
	{
	public:
		ActorBase(const ActorBase& other);
		ActorBase(ActorBase&& other) noexcept;
		virtual ~ActorBase();

		ActorBase& operator=(ActorBase&& other) noexcept;
		ActorBase& operator=(const ActorBase& other);

		void AttachShape(const Ref<ShapeBaseImpl>& shape);
		void DetachShape(const Ref<ShapeBaseImpl>& shape);

		glm::vec3 WorldSpaceToActorSpace(const glm::vec3& worldPoint) const;
		glm::vec3 ActorSpaceToWorldSpace(const glm::vec3& worldPoint) const;

		/// <summary>
		/// Calculates the center of mass of this actor in <b>world space</b>.
		/// </summary>
		/// <returns>Center of Mass in World Space</returns>
		glm::vec3 GetCenterOfMass() const;

	public:
		ActorType GetType() const { return m_Type; }
		const Transform& GetTransform() const { return m_Transform; }

	protected:
		ActorBase(ActorType type, const Transform& spawnTransform);

	private:
		ActorType m_Type = ActorType::None;
		Transform m_Transform;

		Ref<ShapeBaseImpl> m_Shape;
		friend class PhysicsWorldImpl;
	};

}
