#pragma once

class IPhysicsShape;
class IPhysicsActor;
class IPhysicsTrigger;
class IPhysicsApi;

enum PHYSICSTYPE
{
	PHYSICSTYPE_SHAPE,
	PHYSICSTYPE_ACTOR,
	PHYSICSTYPE_TRIGGER,
	PHYSICSTYPE_PHYSICS,
};
typedef unsigned int PHYSICS_OID;

class IPhysicsObject
{
public:
	static IPhysicsShape* GetShape(PHYSICS_OID oid);
	static IPhysicsActor* GetActor(PHYSICS_OID oid);
	static IPhysicsTrigger* GetTrigger(PHYSICS_OID oid);
	static IPhysicsApi* GetPhysics(PHYSICS_OID oid);

private:
	PHYSICSTYPE m_Type;
	PHYSICS_OID m_ObjectId;

protected:
	IPhysicsObject(PHYSICSTYPE type);

public:
	virtual ~IPhysicsObject();

	PHYSICSTYPE GetType();
	unsigned long GetObjectId();

};

class IPhysicsShape : public IPhysicsObject
{
public:
	IPhysicsShape();
};

class IPhysicsActor : public IPhysicsObject
{
public:
	IPhysicsActor();

	virtual unsigned int GetCollisionMask() = 0;
	virtual void SetCollisionMask(unsigned int value) = 0;
	virtual unsigned int GetCollisionFilter() = 0;
	virtual void SetCollisionFilter(unsigned int value) = 0;

	virtual Vector3 GetPosition() = 0;
	virtual void SetPosition(Vector3 value) = 0;
	virtual Quaternion GetRotation() = 0;
	virtual void SetRotation(Quaternion value) = 0;
	virtual Vector3 GetVelocity() = 0;
	virtual void SetVelocity(Vector3 value) = 0;
};

class IPhysicsTrigger : public IPhysicsObject
{
public:
	IPhysicsTrigger();

	virtual std::vector<IPhysicsActor*> GetActors() = 0;
};

class IPhysicsApi : public IPhysicsObject
{
public:
	IPhysicsApi();

	virtual IPhysicsShape* CreateBoxShape(Vector3 extents, Vector3 scaling) = 0;
	virtual IPhysicsShape* CreateSphereShape(float radius, Vector3 scaling) = 0;
	virtual IPhysicsShape* CreateCapsuleShape(float radius, float length, int upAxis, Vector3 scaling) = 0;
	virtual IPhysicsShape* CreateCylinderShape(Vector3 extents, Vector3 scaling) = 0;
	virtual IPhysicsShape* CreateTriangleShape(Vector3* vertices, int count, Vector3 scaling) = 0;
	virtual void DestoryShape(IPhysicsShape* shape) = 0;

	virtual IPhysicsActor* CreateStaticCollision(IPhysicsShape* shape, Vector3 position, Quaternion rotation) = 0;
	virtual IPhysicsActor* CreateDynamicCollision(IPhysicsShape* shape, Vector3 position, Quaternion rotation) = 0;
	virtual IPhysicsActor* CreateActor(IPhysicsShape* shape, Vector3 position, Quaternion rotation) = 0;
	virtual void DestoryActor(IPhysicsActor* actor) = 0;

	virtual IPhysicsTrigger* CreateTrigger(IPhysicsShape* shape, Vector3 position, Quaternion rotation) = 0;
	virtual void DestoryTrigger(IPhysicsTrigger* trigger) = 0;

	virtual std::vector<IPhysicsActor*> Overlap(IPhysicsShape* shape, Vector3 position, Quaternion rotation) = 0;
	virtual std::vector<IPhysicsActor*> Sweep(IPhysicsShape* shape, Vector3 position, Quaternion rotation) = 0;
	virtual bool Raycast(Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation) = 0;
};
