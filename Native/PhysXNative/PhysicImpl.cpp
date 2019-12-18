#include <map>
#include <vector>
#include "PhysicsDefeine.h"
#include "Math.h"

#include "PhysicsApi.h"
#include "PhysicsImpl.h"

unsigned int PhysicsActor::GetCollisionMask()
{
	return 0;
}

void PhysicsActor::SetCollisionMask(unsigned int value)
{
}

unsigned int PhysicsActor::GetCollisionFilter()
{
	return 0;
}

void PhysicsActor::SetCollisionFilter(unsigned int value)
{
}

Vector3 PhysicsActor::GetPosition()
{
	return Vector3();
}

void PhysicsActor::SetPosition(Vector3 value)
{
}

Quaternion PhysicsActor::GetRotation()
{
	return Quaternion();
}

void PhysicsActor::SetRotation(Quaternion value)
{
}

Vector3 PhysicsActor::GetVelocity()
{
	return Vector3();
}

void PhysicsActor::SetVelocity(Vector3 value)
{
}

std::vector<IPhysicsActor*> PhysicsTrigger::GetActors()
{
	return std::vector<IPhysicsActor*>();
}

IPhysicsShape* PhysicsApi::CreateBoxShape(Vector3 enxtents, Vector3 scaling)
{
	return nullptr;
}

IPhysicsShape* PhysicsApi::CreateSphereShape(float radius, Vector3 scaling)
{
	return nullptr;
}

IPhysicsShape* PhysicsApi::CreateCapsuleShape(float radius, float length, int upAxis, Vector3 scaling)
{
	return nullptr;
}

IPhysicsShape* PhysicsApi::CreateCylinderShape(Vector3 enxtents, Vector3 scaling)
{
	return nullptr;
}

IPhysicsShape* PhysicsApi::CreateTriangleShape(Vector3* verteies, int count, Vector3 scaling)
{
	return nullptr;
}

void PhysicsApi::DestoryShape(IPhysicsShape* shape)
{
	delete shape;
}

IPhysicsActor* PhysicsApi::CreateStaticCollision(IPhysicsShape* shape, Vector3 position, Quaternion rotation)
{
	return nullptr;
}

IPhysicsActor* PhysicsApi::CreateDynamicCollision(IPhysicsShape* shape, Vector3 position, Quaternion rotation)
{
	return nullptr;
}

IPhysicsActor* PhysicsApi::CreateActor(IPhysicsShape* shape, Vector3 position, Quaternion rotation)
{
	return nullptr;
}

void PhysicsApi::DestoryActor(IPhysicsActor* actor)
{
	delete actor;
}

IPhysicsTrigger* PhysicsApi::CreateTrigger(IPhysicsShape* shape, Vector3 position, Quaternion rotation)
{
	return nullptr;
}

void PhysicsApi::DestoryTrigger(IPhysicsTrigger* trigger)
{
	delete trigger;
}

std::vector<IPhysicsActor*> PhysicsApi::Overlap(IPhysicsShape* shape, Vector3 position, Quaternion rotation)
{
	return std::vector<IPhysicsActor*>();
}

std::vector<IPhysicsActor*> PhysicsApi::Sweep(IPhysicsShape* shape, Vector3 position, Quaternion rotation)
{
	return std::vector<IPhysicsActor*>();
}

bool PhysicsApi::Raycast(Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation)
{
	return false;
}
