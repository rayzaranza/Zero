#pragma once

#include <functional>
#include <memory>

//==============================================================================================================================================
//  API DLL
//==============================================================================================================================================

#ifdef ZERO_PLATFORM_WINDOWS
    #ifdef ZERO_DYNAMIC_LIBRARY
        #ifdef ZERO_BUILD_DLL
            #define ZERO_API __declspec(dllexport)
        #else
            #define ZERO_API __declspec(dllimport)
        #endif
    #else
        #define ZERO_API
    #endif
#else
    #define ZERO_API
#endif

//==============================================================================================================================================
//  Assertions
//==============================================================================================================================================

#ifdef ZERO_ENABLE_ASSERTS
    #define ZERO_ASSERT(x, ...)                                                                                                                \
        {                                                                                                                                      \
            if (!(x))                                                                                                                          \
            {                                                                                                                                  \
                ZERO_ERROR("Assertion failed: {}", __VA_ARGS__);                                                                               \
                __debugbreak();                                                                                                                \
            }                                                                                                                                  \
        }

    #define ZERO_CORE_ASSERT(x, ...)                                                                                                           \
        {                                                                                                                                      \
            if (!(x))                                                                                                                          \
            {                                                                                                                                  \
                ZERO_CORE_ERROR("Assertion failed: {}", __VA_ARGS__);                                                                          \
                __debugbreak();                                                                                                                \
            }                                                                                                                                  \
        }
#else
    #define ZERO_ASSERT(x, ...)
    #define ZERO_CORE_ASSERT(x, ...)
#endif

//==============================================================================================================================================
//  Event Function Binding
//==============================================================================================================================================

#define ZERO_BIND_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

//==============================================================================================================================================
//  Ref and Scope
//==============================================================================================================================================

namespace Zero
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;
}
