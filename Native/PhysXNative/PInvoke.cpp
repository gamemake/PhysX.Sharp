#include <map>
#include <vector>
#include "PhysicsDefeine.h"
#include "Math.h"

#include "PhysicsApi.h"
#include "PhysicsImpl.h"
#include "Log.h"

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
	if (objects.size() == 0) return nullptr;

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
	LogWrite("On PhysicsApi_New");

	auto physics = new PhysicsApi();
	return physics->GetObjectId();
}

PINVOKE_API void PhysicsApi_Delete(PHYSICS_OID oid)
{
	LogWrite("On PhysicsApi_Delete %d", oid);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;
	delete physics;
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateBoxShape(PHYSICS_OID oid, Vector3 extents, Vector3 scaling)
{
	LogWrite("On PhysicsApi_CreateBoxShape %d, (%f,%f,%f), (%f,%f,%f)", oid, extents.x, extents.y, extents.z, scaling.x, scaling.y, scaling.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateBoxShape(extents, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateSphereShape(PHYSICS_OID oid, float radius, Vector3 scaling)
{
	LogWrite("On PhysicsApi_CreateSphereShape %d, %f, (%f,%f,%f)", oid, radius, scaling.x, scaling.y, scaling.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateSphereShape(radius, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateCapsuleShape(PHYSICS_OID oid, float radius, float length, int upAxis, Vector3 scaling)
{
	LogWrite("On PhysicsApi_CreateCapsuleShape %d, %f, %f, %d, (%f,%f,%f)", oid, radius, length, upAxis, scaling.x, scaling.y, scaling.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateCapsuleShape(radius, length, upAxis, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateCylinderShape(PHYSICS_OID oid, Vector3 extents, Vector3 scaling)
{
	LogWrite("On PhysicsApi_CreateCylinderShape %d, (%f,%f,%f), (%f,%f,%f)", oid, extents.x, extents.y, extents.z, scaling.x, scaling.y, scaling.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateCylinderShape(extents, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateTriangleShape(PHYSICS_OID oid, Vector3* vertices, int count, Vector3 scaling)
{
	LogWrite("On PhysicsApi_CreateCylinderShape %d, (%f,%f,%f)-(%f,%f,%f), %d, (%f,%f,%f)", oid, vertices[0].x, vertices[0].y, vertices[0].z, vertices[count - 1].x, vertices[count - 1].y, vertices[count - 1].z, count, scaling.x, scaling.y, scaling.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateTriangleShape(vertices, count, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API void PhysicsApi_DestoryShape(PHYSICS_OID oid, PHYSICS_OID shape)
{
	LogWrite("On PhysicsApi_DestoryShape %d, %d", oid, shape);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return;

	physics->DestoryShape(_shape);
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateStaticCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	LogWrite("On PhysicsApi_CreateStaticCollision %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, shape, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateStaticCollision(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateDynamicCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	LogWrite("On PhysicsApi_CreateDynamicCollision %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, shape, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateDynamicCollision(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateActor(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	LogWrite("On PhysicsApi_CreateActor %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, shape, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateActor(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API void PhysicsApi_DestoryActor(PHYSICS_OID oid, PHYSICS_OID actor)
{
	LogWrite("On PhysicsApi_DestoryActor %d, %d", oid, actor);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _actor = IPhysicsObject::GetActor(actor);
	if (_actor == nullptr) return;

	physics->DestoryActor(_actor);
}

PINVOKE_API PHYSICS_OID PhysicsApi_CreateTrigger(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	LogWrite("On PhysicsApi_CreateTrigger %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, shape, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto trigger = physics->CreateTrigger(_shape, position, rotation);
	if (trigger == nullptr) return (PHYSICS_OID)-1;

	return trigger->GetObjectId();
}

PINVOKE_API void PhysicsApi_DestoryTrigger(PHYSICS_OID oid, PHYSICS_OID trigger)
{
	LogWrite("On PhysicsApi_DestoryTrigger %d, %d", oid, trigger);

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _trigger = IPhysicsObject::GetTrigger(trigger);
	if (_trigger == nullptr) return;

	physics->DestoryTrigger(_trigger);
}

PINVOKE_API PHYSICS_OID* PhysicsApi_Overlap(PHYSICS_OID oid, unsigned int filter, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
{
	LogWrite("On PhysicsApi_Overlap %d, %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, filter, shape, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	static std::vector<PHYSICS_OID> retval;
	count = 0;

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return nullptr;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return nullptr;

	auto objects = physics->Overlap(filter, _shape, position, rotation);
	if (objects.size() == 0) return nullptr;

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

PINVOKE_API PHYSICS_OID* PhysicsApi_Sweep(PHYSICS_OID oid, unsigned int filter, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
{
	LogWrite("On PhysicsApi_Sweep %d, %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, filter, shape, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	static std::vector<PHYSICS_OID> retval;
	count = 0;

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return nullptr;

	auto _shape = IPhysicsObject::GetShape(shape);
	if (_shape == nullptr) return nullptr;

	auto objects = physics->Sweep(filter, _shape, position, rotation);
	if (objects.size() == 0) return nullptr;

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

PINVOKE_API bool PhysicsApi_Raycast(PHYSICS_OID oid, unsigned int filter, Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation)
{
	LogWrite("On PhysicsApi_Raycast %d, %d, (%f,%f,%f), (%f, %f,%f,%f)", oid, filter, position.x, position.y, position.z, rotation.w, rotation.x, rotation.y, rotation.z);

	actor = nullptr;
	hitPosition = Vector3();
	hitRotation = Quaternion();

	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return false;

	return physics->Raycast(filter, position, rotation, actor, hitPosition, hitRotation);
}
