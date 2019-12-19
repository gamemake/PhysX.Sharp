
namespace PhysX.Sharp
{
    using System.Runtime.InteropServices;

    public static class Native
    {
#if UNITY_IOS && !UNITY_EDITOR
        public const string Dll = "__Internal";
#else
        public const string Dll = "PhysXNative";
#endif
        //        public const string Dll = "libbulletc.dll";
        public const CallingConvention Conv = CallingConvention.Cdecl;

    }
}
