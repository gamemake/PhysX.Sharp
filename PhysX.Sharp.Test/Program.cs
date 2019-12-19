using System;
using System.Numerics;

namespace PhysX.Sharp.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var physics = PhysicsApi.New();
            var box = physics.CreateBoxShape(new Vector3(1f, 2f, 3f), new Vector3(4f, 5f, 6f));
            var vertices = new Vector3[] { new Vector3(1f, 2f, 3f), new Vector3(4f, 5f, 6f), new Vector3(7f, 8f, 9f), new Vector3(10f, 11f, 12f) };
            var triangle = physics.CreateTriangleShape(vertices, vertices.Length, new Vector3(.4f, .5f, .6f));
            foreach (var actor in physics.Sweep(0, box, new Vector3(1f, 2f, 3f), new Quaternion(4f, 5f, 6f, 7f)))
            {
                Console.WriteLine("{0}", actor.ObjectId);
            }
            physics.DestoryShape(box);
            physics.DestoryShape(triangle);
            PhysicsApi.Delete(physics);
        }
    }
}
