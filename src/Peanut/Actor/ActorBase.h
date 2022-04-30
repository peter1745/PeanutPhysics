#pragma once

#include "Collision/Shape.h"

#include <vector>

namespace Peanut {

	enum class ActorType : int8_t
	{
		None = -1, Static, Dynamic
	};

	class ActorBase
	{
	public:
		ActorBase(const ActorBase& other);
		ActorBase(ActorBase&& other) noexcept;
		virtual ~ActorBase();

		ActorBase& operator=(ActorBase&& other) noexcept;
		ActorBase& operator=(const ActorBase& other);

		void AttachShape(const Shape& shape);
		Shape FindShapeOfType(GeometryType shapeType) const;
		void DetachShape(const Shape& shape);

	public:
		ActorType GetType() const { return m_Type; }
		const Transform& GetTransform() const { return m_Transform; }

	protected:
		ActorBase(ActorType type, const Transform& spawnTransform);

	private:
		// Would probably be fine having this as 16-bit initially, but in case we want to support >65,535 dynamic actors we'll keep it as 32-bit
		uint32_t m_ActorID = 0;
		ActorType m_Type = ActorType::None;
		Transform m_Transform;

		std::vector<Shape> m_Shapes;
		friend class PhysicsWorldImpl;
	};

}
