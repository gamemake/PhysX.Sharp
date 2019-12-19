using System;

namespace PhysX.Sharp.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var physics = PhysicsApi.New();
            PhysicsApi.Delete(physics);
        }
    }
}
