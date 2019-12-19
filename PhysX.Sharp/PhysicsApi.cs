
namespace PhysX.Sharp
{
    using System;
    using System.Security;
    using System.Runtime.InteropServices;
    using System.Numerics;

    public class PhysicsApi : PhysicsObject
    {
        public static PhysicsApi New()
        {
            var oid = PhysicsApi_New();
            return Get<PhysicsApi>(oid);
        }

        public static void Delete(PhysicsApi physics)
        {
            PhysicsApi_Delete(physics.ObjectId);
        }

        public PhysicsApi(uint oid) : base(oid)
        {
        }

        public PhysicsShape CreateBoxShape(Vector3 extents, Vector3 scaling)
        {
            var oid = PhysicsApi_CreateBoxShape(ObjectId, extents, scaling);
            return Get<PhysicsShape>(oid);
        }

        public PhysicsShape CreateSphereShape(float radius, Vector3 scaling)
        {
            var oid = PhysicsApi_CreateSphereShape(ObjectId, radius, scaling);
            return Get<PhysicsShape>(oid);
        }

        public PhysicsShape CreateCapsuleShape(float radius, float length, int upAxis, Vector3 scaling)
        {
            var oid = PhysicsApi_CreateCapsuleShape(ObjectId, radius, length, upAxis, scaling);
            return Get<PhysicsShape>(oid);
        }

        public PhysicsShape CreateCylinderShape(Vector3 extents, Vector3 scaling)
        {
            var oid = PhysicsApi_CreateCylinderShape(ObjectId, extents, scaling);
            return Get<PhysicsShape>(oid);
        }

        public PhysicsShape CreateTriangleShape(Vector3[] vertices, int count, Vector3 scaling)
        {
            var oid = PhysicsApi_CreateTriangleShape(ObjectId, vertices, vertices.Length, scaling);
            return Get<PhysicsShape>(oid);
        }

        public void DestoryShape(PhysicsShape shape)
        {
            PhysicsApi_DestoryShape(ObjectId, shape.ObjectId);
        }

        // PINVOKE_API PHYSICS_OID PhysicsApi_New()
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_New();

        // PINVOKE_API void PhysicsApi_Delete(PHYSICS_OID oid)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_Delete(uint oid);

        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateBoxShape(PHYSICS_OID oid, Vector3 extents, Vector3 scaling)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_CreateBoxShape(uint oid, Vector3 extents, Vector3 scaling);

        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateSphereShape(PHYSICS_OID oid, float radius, Vector3 scaling)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_CreateSphereShape(uint oid, float radius, Vector3 scaling);

        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateCapsuleShape(PHYSICS_OID oid, float radius, float length, int upAxis, Vector3 scaling)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_CreateCapsuleShape(uint oid, float radius, float length, int upAxis, Vector3 scaling);

        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateCylinderShape(PHYSICS_OID oid, Vector3 enxtents, Vector3 scaling)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_CreateCylinderShape(uint oid, Vector3 extents, Vector3 scaling);

        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateTriangleShape(PHYSICS_OID oid, Vector3* vertices, int count, Vector3 scaling)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern uint PhysicsApi_CreateTriangleShape(uint oid, [In] Vector3[] vertices, int count, Vector3 scaling);

        // PINVOKE_API void PhysicsApi_DestoryShape(PHYSICS_OID oid, PHYSICS_OID shape)
        [DllImport(Native.Dll, CallingConvention = Native.Conv), SuppressUnmanagedCodeSecurity]
        private static extern void PhysicsApi_DestoryShape(uint oid, uint shape);

        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateStaticCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateDynamicCollision(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateActor(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
        // PINVOKE_API void PhysicsApi_DestoryActor(PHYSICS_OID oid, PHYSICS_OID actor)
        // PINVOKE_API PHYSICS_OID PhysicsApi_CreateTrigger(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation)
        // PINVOKE_API void PhysicsApi_DestoryTrigger(PHYSICS_OID oid, PHYSICS_OID trigger)
        // PINVOKE_API PHYSICS_OID* PhysicsApi_Overlap(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
        // PINVOKE_API PHYSICS_OID* PhysicsApi_Sweep(PHYSICS_OID oid, PHYSICS_OID shape, Vector3 position, Quaternion rotation, int& count)
        // PINVOKE_API bool PhysicsApi_Raycast(PHYSICS_OID oid, Vector3 position, Quaternion rotation, IPhysicsActor*& actor, Vector3& hitPosition, Quaternion& hitRotation)
    }
}
