
namespace PhysX.Sharp
{
    using System;
    using System.Collections.Generic;

    public abstract class PhysicsObject
    {
        private static Dictionary<uint, PhysicsObject> m_Objects = new Dictionary<uint, PhysicsObject>();
        protected static T Get<T>(uint oid) where T : PhysicsObject
        {
            if (oid == uint.MaxValue) return null;

            if (m_Objects.ContainsKey(oid))
            {
                var obj = m_Objects[oid];
                if (obj.GetType() != typeof(T) && !obj.GetType().IsSubclassOf(typeof(T)))
                {
                    throw new Exception("invalid object type");
                }
                return (T)obj;
            }
            else
            {
                var obj = (T)Activator.CreateInstance(typeof(T), oid);
                Add<T>(oid, obj);
                return obj;
            }
        }
        protected static void Add<T>(uint oid, T obj) where T : PhysicsObject
        {
            m_Objects.Add(oid, obj);
        }

        public uint ObjectId { get; private set; }

        public PhysicsObject(uint oid)
        {
            ObjectId = oid;
        }
    }
}
