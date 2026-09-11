#pragma once

#include <functional>
#include <memory>

//===============================================================================================
//  Platform
//===============================================================================================

#ifdef _WIN32
#   define ZR_PLATFORM_WINDOWS

#elif defined(__APPLE__) || defined(__MACH__)
#    include <TargetConditionals.h>
#    if TARGET_IPHONE_SIMULATOR == 1
#        error "IOS simulator is not supported"
#    elif TARGET_OS_IPHONE == 1
#        error "IOS is not supported"
#    elif TARGET_OS_MAC == 1
#        define ZR_PLATFORM_MACOS
#        error "MacOS is not supported"
#    else
#        define ZR_PLATOFMR_APPLE_UNKNOWN
#        error "Unknow Apple platform"
#    endif

#elif defined(__ANDROID__)
#    define ZR_PLATFORM_ANDROID
#    error "Android is not supported"

#elif defined(__linux__)
#   define ZR_PLATFORM_LINUX
#   error "Linux is not supported"

#else
#   define ZR_PLATFORM_UNKNOWN
#   error "Unknown platorm"

#endif

//===============================================================================================
//  Assertions
//===============================================================================================

#ifdef ZR_ENABLE_ASSERTS
#   define ZR_ASSERT(x, ...)                                                                                                                   \
    {                                                                                                                                          \
        if (!(x))                                                                                                                              \
        {                                                                                                                                      \
            ZR_ERROR("Assertion failed: {}", __VA_ARGS__);                                                                                     \
            __debugbreak();                                                                                                                    \
        }                                                                                                                                      \
    }
#   define ZR_CORE_ASSERT(x, ...)                                                                                                              \
    {                                                                                                                                          \
        if (!(x))                                                                                                                              \
        {                                                                                                                                      \
            ZR_CORE_ERROR("Assertion failed: {}", __VA_ARGS__);                                                                                \
            __debugbreak();                                                                                                                    \
        }                                                                                                                                      \
    }
#else
#   define ZR_ASSERT(x, ...)
#   define ZR_CORE_ASSERT(x, ...)
#endif

//===============================================================================================
//  Event Function Binding
//===============================================================================================

#define ZR_BIND_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

//===============================================================================================
//  Ref and Scope
//===============================================================================================

namespace Zero
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;
}
