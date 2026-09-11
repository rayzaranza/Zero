#pragma once

#include <array>
#include <functional>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

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
//  Aliases
//===============================================================================================
namespace Zero
{
    //===========================================================================================
    using F32 = float;
    using F64 = double;
    using U8 = uint8_t;
    using U16 = uint16_t;
    using U32 = uint32_t;
    using U64 = uint64_t;
    using I8 = int8_t;
    using I16 = int16_t;
    using I32 = int32_t;
    using I64 = int64_t;
    using String = std::string;
    using Boolean = bool;
    using Length = size_t;

    //===========================================================================================
    template <typename T> using Array = std::vector<T>;
    template <typename T, Length S> using FixedArray = std::array<T, S>;
    template <typename K, typename V> using Map = std::unordered_map<K, V>;
    template <typename A, typename B> using Pair = std::pair<A, B>;
    template <typename T> using Function = std::function<T>;

    //===========================================================================================
    template <typename T> using Scope = std::unique_ptr<T>;
    template <typename T> using Ref = std::shared_ptr<T>;
    template <typename T> using WeakRef = std::weak_ptr<T>;

    //===========================================================================================
    using Vector3 = glm::vec3;
    using Vector2 = glm::vec2;
    using Vector4 = glm::vec4;
    using Matrix4 = glm::mat4;
    using Matrix3 = glm::mat3;
    using Quaternion = glm::quat;
    using Color = glm::vec4;

    //===========================================================================================
    using RendererID = U32;

    //===========================================================================================
    template <typename T, typename... TArgs>
    constexpr Ref<T> CreateRef(TArgs&&... args)
    {
        return std::make_shared<T>(std::forward<TArgs>(args)...);
    }

    template <typename T, typename... TArgs>
    constexpr Ref<T> CreateScope(TArgs&&... args)
    {
        return std::make_unique<T>(std::forward<TArgs>(args)...);
    }
}
