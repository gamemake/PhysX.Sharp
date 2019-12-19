#pragma once

#include <map>
#include <vector>
#include "PhysicsDefeine.h"
#include "Math.h"

#include "PhysicsApi.h"
#include "Log.h"

class ObjectTable
{
private:
	IPhysicsObject** m_Objects;
	unsigned int m_Count;
	unsigned int m_Seq;

public:
	ObjectTable(unsigned int count)
	{
		m_Objects = new IPhysicsObject * [count];
		m_Count = count;
		m_Seq = 0;
		for (unsigned int i = 0; i < count; i++)
		{
			m_Objects[i] = nullptr;
		}
	}

	PHYSICS_OID Register(IPhysicsObject* object)
	{
		for (unsigned long i = 0; i < m_Count; i++)
		{
			if (m_Objects[i] == nullptr)
			{
				auto oid = i | ((m_Seq++) << 16);
				m_Objects[i] = object;
				return oid;
			}
		}
		return (unsigned long)-1;
	}

	void Unregister(IPhysicsObject* object, PHYSICS_OID oid)
	{
		auto index = oid & 0xffff;
		if (index < m_Count && m_Objects[index] == object)
		{
			m_Objects[index] = nullptr;
		}
	}

	IPhysicsObject* Get(unsigned long oid, PHYSICSTYPE type)
	{
		auto index = oid & 0xffff;
		if (index >= m_Count)
		{
			LogWrite("object [%d] id out of range", oid);
			return nullptr;
		}

		auto obj = m_Objects[index];
		if (obj == nullptr)
		{
			LogWrite("object [%d] not found", oid);
			return nullptr;
		}

		if (obj->GetType() != type)
		{
			LogWrite("object [%d] type not match, %d %d", oid, obj->GetType(), type);
			return nullptr;
		}

		return obj;
	}
};

static ObjectTable objectTable(4000);

IPhysicsShape* IPhysicsObject::GetShape(PHYSICS_OID oid)
{
	return (IPhysicsShape*)objectTable.Get(oid, PHYSICSTYPE_SHAPE);
}

IPhysicsActor* IPhysicsObject::GetActor(PHYSICS_OID oid)
{
	return (IPhysicsActor*)objectTable.Get(oid, PHYSICSTYPE_ACTOR);
}

IPhysicsTrigger* IPhysicsObject::GetTrigger(PHYSICS_OID oid)
{
	return (IPhysicsTrigger*)objectTable.Get(oid, PHYSICSTYPE_TRIGGER);
}

IPhysicsApi* IPhysicsObject::GetPhysics(PHYSICS_OID oid)
{
	return (IPhysicsApi*)objectTable.Get(oid, PHYSICSTYPE_PHYSICS);
}

IPhysicsObject::IPhysicsObject(PHYSICSTYPE type)
{
	m_Type = type;
	m_ObjectId = objectTable.Register(this);
}

IPhysicsObject::~IPhysicsObject()
{
	objectTable.Unregister(this, m_Type);
}

PHYSICSTYPE IPhysicsObject::GetType()
{
	return m_Type;
}

unsigned long IPhysicsObject::GetObjectId()
{
	return m_ObjectId;
}

IPhysicsShape::IPhysicsShape() : IPhysicsObject(PHYSICSTYPE_SHAPE)
{
}

IPhysicsActor::IPhysicsActor() : IPhysicsObject(PHYSICSTYPE_ACTOR)
{
}

IPhysicsTrigger::IPhysicsTrigger() : IPhysicsObject(PHYSICSTYPE_TRIGGER)
{
}

IPhysicsApi::IPhysicsApi() : IPhysicsObject(PHYSICSTYPE_PHYSICS)
{
}
