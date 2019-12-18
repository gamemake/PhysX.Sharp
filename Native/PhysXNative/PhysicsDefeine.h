#pragma once

#ifdef _WIN32
    #define PINVOKE_API extern "C" __declspec(dllexport)
#else
    #ifdef _WIN64
        #define PINVOKE_API extern "C" __declspec(dllexport)
    #else
        #define PINVOKE_API extern "C"
    #endif
#endif
