#pragma once

// ·······················································································································
//  API DLL
// ·······················································································································
#ifdef ZERO_PLATFORM_WINDOWS
    #ifdef ZERO_BUILD_DLL
        #define ZERO_API __declspec(dllexport)
    #else
        #define ZERO_API __declspec(dllimport)
    #endif
#else
    #define ZERO_API
#endif

// ·······················································································································
//  Assertions
// ·······················································································································
#ifdef ZERO_ENABLE_ASSERTS
    #define ZERO_ASSERT(x, ...)                                                                                        \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                ZERO_ERROR("Assertion failed: {}", __VA_ARGS__);                                                       \
                __debugbreak();                                                                                        \
            }                                                                                                          \
        }

    #define ZERO_CORE_ASSERT(x, ...)                                                                                   \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                ZERO_CORE_ERROR("Assertion failed: {}", __VA_ARGS__);                                                  \
                __debugbreak();                                                                                        \
            }                                                                                                          \
        }
#else
    #define ZERO_ASSERT(x, ...)
    #define ZERO_CORE_ASSERT(x, ...)
#endif

// ·······················································································································
//  Bit Shifting
// ·······················································································································
#define BIT(x) (1 << x)
