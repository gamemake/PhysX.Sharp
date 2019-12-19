#include <map>
#include <vector>
#include "PhysicsDefeine.h"
#include "Math.h"

#include "PhysicsApi.h"
#include "PhysicsImpl.h"

PINVOKE_API unsigned int PhysicsActor_GetCollisionMask(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return 0;
	return actor->GetCollisionMask();
}

PINVOKE_API void PhysicsActor_SetCollisionMask(PHYSICS_OID oid, unsigned int value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetCollisionMask(value);
}

PINVOKE_API unsigned int PhysicsActor_GetCollisionFilter(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return 0;
	return actor->GetCollisionFilter();
}

PINVOKE_API void PhysicsActor_SetCollisionFilter(PHYSICS_OID oid, unsigned int value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetCollisionFilter(value);
}

PINVOKE_API Vector3 PhysicsActor_GetPosition(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return Vector3();
	return actor->GetPosition();
}

PINVOKE_API void PhysicsActor_SetPosition(PHYSICS_OID oid, Vector3 value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetPosition(value);
}

PINVOKE_API Quaternion PhysicsActor_GetRotation(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return Quaternion();
	return actor->GetRotation();
}

PINVOKE_API void PhysicsActor_SetRotation(PHYSICS_OID oid, Quaternion value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetRotation(value);
}

PINVOKE_API Vector3 PhysicsActor_GetVelocity(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return Vector3();
	return actor->GetVelocity();
}

PINVOKE_API void PhysicsActor_SetVelocity(PHYSICS_OID oid, Vector3 value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetVelocity(value);
}

PINVOKE_API PHYSICS_OID* PhysicsTrigger_GetActors(PHYSICS_OID oid, int& count)
{
	static std::vector<PHYSICS_OID> retval;
	count = 0;

	auto trigger = IPhysicsObject::GetTrigger(oid);
	if (trigger == nullptr) return nullptr;

	auto objects = trigger->GetActors();
	for (auto i = 0; i < objects.size(); i++)
	{
		if (i >= retval.size())
		{
			retval.push_back(objects[i]->GetObjectId());
		}
		else
		{
			retval[i] = objects[i]->GetObjectId();
		}
	}

	count = (int)objects.size();
	return &retval[0];
}

PINVOKE_API PHYSICS_OID PhysicsApi_New()
{
	auto physics = new PhysicsApi();
	return physics->GetObjectId();
}

PINVOKE_API void PhysicsApi_Delete(PHYSICS_OID oid)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;
	delete physics;
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateBoxShape(PHYSICS_OID oid, Vector3 enxtents, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateBoxShape(enxtents, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateSphereShape(PHYSICS_OID oid, float radius, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateSphereShape(radius, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateCapsuleShape(PHYSICS_OID oid, float radius, float length, int upAxis, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateCapsuleShape(radius, length, upAxis, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateCylinderShape(PHYSICS_OID oid, Vector3 enxtents, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateCylinderShape(enxtents, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateTriangleShape(PHYSICS_OID oid, Vector3* vertices, int count, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateTriangleShape(vertices, count, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API void PhysicsApi_DestoryShape(PHYSICS_OID oid, PHYSICS_OID shape)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return;

	physics->DestoryShape(_shape);
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateStaticCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateStaticCollision(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateDynamicCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateDynamicCollision(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateActor(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateActor(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API void PhysicsApi_DestoryActor(PHYSICS_OID oid, PHYSICS_OID actor)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _actor = IPhysicsObject::GetActor(oid);
	if (_actor == nullptr) return;

	physics->DestoryActor(_actor);
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateTrigger(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto trigger = physics->CreateTrigger(_shape, position, rotation);
	if (trigger == nullptr) return (PHYSICS_OID)-1;

	return trigger->GetObjectId();
}

PINVOKE_API void PhysicsApi_DestoryTrigger(PHYSICS_OID oid, PHYSICS_OID trigger)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _trigger = IPhysicsObject::GetTrigger(oid);
	if (_trigger == nullptr) return;

	physics->DestoryTrigger(_trigger);
}

PINVOKE_API PHYSICS_OID* PhysicsApi_Overlap(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
{
	static std::vector<PHYSICS_OID> retval;
	count = 0;

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return nullptr;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return nullptr;

	auto objects = physics->Overlap(_shape, position, rotation);
	for (auto i = 0; i < objects.size(); i++)
	{
		if (i >= retval.size())
		{
			retval.push_back(objects[i]->GetObjectId());
		}
		else
		{
			retval[i] = objects[i]->GetObjectId();
		}
	}

	count = (int)objects.size();
	return &retval[0];
}

PINVOKE_API PHYSICS_OID* PhysicsApi_Sweep(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
{
	static std::vector<PHYSICS_OID> retval;
	count = 0;

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return nullptr;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return nullptr;

	auto objects = physics->Sweep(_shape, position, rotation);
	for (auto i = 0; i < objects.size(); i++)
	{
		if (i >= retval.size())
		{
			retval.push_back(objects[i]->GetObjectId());
		}
		else
		{
			retval[i] = objects[i]->GetObjectId();
		}
	}

	count = (int)objects.size();
	return &retval[0];
}

PINVOKE_API bool PhysicsApi_Raycast(PHYSICS_OID oid, Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation)
{
	actor = nullptr;
	hitPosition = Vector3();
	hitRotation = Quaternion();

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return false;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return false;

	return physics->Raycast(position, rotation, actor, hitPosition, hitRotation);
}
