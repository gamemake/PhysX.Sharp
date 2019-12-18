#include <map>
#include <vector>
#include "PhysicsDefeine.h"
#include "Math.h"

#include "PhysicsApi.h"
#include "PhysicsImpl.h"

unsigned int IPhysicsActor_GetCollisionMask(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return 0;
	return actor->GetCollisionMask();
}

void IPhysicsActor_SetCollisionMask(PHYSICS_OID oid, unsigned int value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetCollisionMask(value);
}

unsigned int IPhysicsActor_GetCollisionFilter(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return 0;
	return actor->GetCollisionFilter();
}

void IPhysicsActor_SetCollisionFilter(PHYSICS_OID oid, unsigned int value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetCollisionFilter(value);
}

Vector3 IPhysicsActor_GetPosition(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return Vector3();
	return actor->GetPosition();
}

void IPhysicsActor_SetPosition(PHYSICS_OID oid, Vector3 value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetPosition(value);
}

Quaternion IPhysicsActor_GetRotation(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return Quaternion();
	return actor->GetRotation();
}

void IPhysicsActor_SetRotation(PHYSICS_OID oid, Quaternion value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetRotation(value);
}

Vector3 IPhysicsActor_GetVelocity(PHYSICS_OID oid)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return Vector3();
	return actor->GetVelocity();
}

void IPhysicsActor_SetVelocity(PHYSICS_OID oid, Vector3 value)
{
	auto actor = IPhysicsObject::GetActor(oid);
	if (actor == nullptr) return;
	actor->SetVelocity(value);
}

PHYSICS_OID* IPhysicsTrigger_GetActors(PHYSICS_OID oid, int& count)
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

PINVOKE_API PHYSICS_OID IPhysicsApi_New()
{
	auto physics = new PhysicsApi();
	return physics->GetObjectId();
}

PINVOKE_API void IPhysicsApi_Delete(PHYSICS_OID oid)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;
	delete physics;
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateBoxShape(PHYSICS_OID oid, Vector3 enxtents, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateBoxShape(enxtents, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateSphereShape(PHYSICS_OID oid, float radius, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateSphereShape(radius, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateCapsuleShape(PHYSICS_OID oid, float radius, float length, int upAxis, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateCapsuleShape(radius, length, upAxis, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateCylinderShape(PHYSICS_OID oid, Vector3 enxtents, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateCylinderShape(enxtents, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateTriangleShape(PHYSICS_OID oid, Vector3* vertices, int count, Vector3 scaling)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto shape = physics->CreateTriangleShape(vertices, count, scaling);
	if (shape == nullptr) return (PHYSICS_OID)-1;

	return shape->GetObjectId();
}

PINVOKE_API void IPhysicsApi_DestoryShape(PHYSICS_OID oid, PHYSICS_OID shape)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return;

	physics->DestoryShape(_shape);
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateStaticCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateStaticCollision(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateDynamicCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateDynamicCollision(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateActor(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto actor = physics->CreateActor(_shape, position, rotation);
	if (actor == nullptr) return (PHYSICS_OID)-1;

	return actor->GetObjectId();
}

PINVOKE_API void IPhysicsApi_DestoryActor(PHYSICS_OID oid, PHYSICS_OID actor)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _actor = IPhysicsObject::GetActor(oid);
	if (_actor == nullptr) return;

	physics->DestoryActor(_actor);
}

PINVOKE_API PHYSICS_OID IPhysicsApi_CreateTrigger(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return (PHYSICS_OID)-1;

	auto _shape = IPhysicsObject::GetShape(oid);
	if (_shape == nullptr) return (PHYSICS_OID)-1;

	auto trigger = physics->CreateTrigger(_shape, position, rotation);
	if (trigger == nullptr) return (PHYSICS_OID)-1;

	return trigger->GetObjectId();
}

PINVOKE_API void IPhysicsApi_DestoryTrigger(PHYSICS_OID oid, PHYSICS_OID trigger)
{
	auto physics = IPhysicsObject::GetPhysics(oid);
	if (physics == nullptr) return;

	auto _trigger = IPhysicsObject::GetTrigger(oid);
	if (_trigger == nullptr) return;

	physics->DestoryTrigger(_trigger);
}

PINVOKE_API PHYSICS_OID* IPhysicsApi_Overlap(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
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

PINVOKE_API PHYSICS_OID* IPhysicsApi_Sweep(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
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

PINVOKE_API bool IPhysicsApi_Raycast(PHYSICS_OID oid, Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation)
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
