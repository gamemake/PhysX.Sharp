#pragma once

class PhysicsShape : public IPhysicsShape
{
public:
};

class PhysicsActor : public IPhysicsActor
{
public:
	virtual unsigned int GetCollisionMask();
	virtual void SetCollisionMask(unsigned int value);
	virtual unsigned int GetCollisionFilter();
	virtual void SetCollisionFilter(unsigned int value);

	virtual Vector3 GetPosition();
	virtual void SetPosition(Vector3 value);
	virtual Quaternion GetRotation();
	virtual void SetRotation(Quaternion value);
	virtual Vector3 GetVelocity();
	virtual void SetVelocity(Vector3 value);
};

class PhysicsTrigger : public IPhysicsTrigger
{
public:
	virtual std::vector<IPhysicsActor*> GetActors();
};

class PhysicsApi : public IPhysicsApi
{
public:
	virtual IPhysicsShape* CreateBoxShape(Vector3 extents, Vector3 scaling);
	virtual IPhysicsShape* CreateSphereShape(float radius, Vector3 scaling);
	virtual IPhysicsShape* CreateCapsuleShape(float radius, float length, int upAxis, Vector3 scaling);
	virtual IPhysicsShape* CreateCylinderShape(Vector3 extents, Vector3 scaling);
	virtual IPhysicsShape* CreateTriangleShape(Vector3* vertices, int count, Vector3 scaling);
	virtual void DestoryShape(IPhysicsShape* shape);

	virtual IPhysicsActor* CreateStaticCollision(IPhysicsShape* shape, Vector3 position, Quaternion rotation);
	virtual IPhysicsActor* CreateDynamicCollision(IPhysicsShape* shape, Vector3 position, Quaternion rotation);
	virtual IPhysicsActor* CreateActor(IPhysicsShape* shape, Vector3 position, Quaternion rotation);
	virtual void DestoryActor(IPhysicsActor* actor);

	virtual IPhysicsTrigger* CreateTrigger(IPhysicsShape* shape, Vector3 position, Quaternion rotation);
	virtual void DestoryTrigger(IPhysicsTrigger* trigger);

	virtual std::vector<IPhysicsActor*> Overlap(IPhysicsShape* shape, Vector3 position, Quaternion rotation);
	virtual std::vector<IPhysicsActor*> Sweep(IPhysicsShape* shape, Vector3 position, Quaternion rotation);
	virtual bool Raycast(Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation);
};
