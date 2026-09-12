#pragma once

#include <array>
#include <functional>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Zero
{
    //===========================================================================================
    //  Primitives
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

    using Degrees = F32;
    using Seconds = F32;
    using Milliseconds = F32;

    using RendererID = U32;

    //===========================================================================================
    //  Containers
    //===========================================================================================
    template <typename T> using Array = std::vector<T>;
    template <typename T, Length S> using FixedArray = std::array<T, S>;
    template <typename K, typename V> using Map = std::unordered_map<K, V>;
    template <typename A, typename B> using Pair = std::pair<A, B>;

    //===========================================================================================
    //  Pointers
    //===========================================================================================
    template <typename T> using Scope = std::unique_ptr<T>;
    template <typename T> using Ref = std::shared_ptr<T>;
    template <typename T> using WeakRef = std::weak_ptr<T>;

    //===========================================================================================
    //  Functions
    //===========================================================================================
    template <typename T> using Function = std::function<T>;

    template <typename T, typename... TArgs>
    constexpr Ref<T> CreateRef(TArgs&&... args)
    {
        return std::make_shared<T>(std::forward<TArgs>(args)...);
    }

    //===============================================================================================================================
    //  Vector4
    //===============================================================================================================================
    using Vector4 = glm::vec4;

    //===============================================================================================================================
    //  Vector3
    //===============================================================================================================================
    struct Vector3 : public glm::vec3
    {
        using glm::vec3::vec3;
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Forward;
        static const Vector3 Backward;
    };

    inline const Vector3 Vector3::Zero{ 0.0f, 0.0f, 0.0f };
    inline const Vector3 Vector3::One{ 1.0f, 1.0f, 1.0f };
    inline const Vector3 Vector3::Up{ 0.0f, 1.0f, 0.0f };
    inline const Vector3 Vector3::Down{ 0.0f, -1.0f, 0.0f };
    inline const Vector3 Vector3::Left{ -1.0f, 0.0f, 0.0f };
    inline const Vector3 Vector3::Right{ 1.0f, 0.0f, 0.0f };
    inline const Vector3 Vector3::Forward{ 0.0f, 0.0f, -1.0f };
    inline const Vector3 Vector3::Backward{ 0.0f, 0.0f, 1.0f };

    //===============================================================================================================================
    //  Vector2
    //===============================================================================================================================
    struct Vector2 : public glm::vec2
    {
        using glm::vec2::vec2;
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 Up;
        static const Vector2 Down;
        static const Vector2 Left;
        static const Vector2 Right;
    };

    inline const Vector2 Vector2::Zero{ 0.0f, 0.0f };
    inline const Vector2 Vector2::One{ 1.0f, 1.0f };
    inline const Vector2 Vector2::Up{ 0.0f, 1.0f };
    inline const Vector2 Vector2::Down{ 0.0f, -1.0f };
    inline const Vector2 Vector2::Left{ -1.0f, 0.0f };
    inline const Vector2 Vector2::Right{ 1.0f, 0.0f };

    //===============================================================================================================================
    //  Vectors Int
    //===============================================================================================================================
    using Vector2i = glm::ivec2;
    using Vector3i = glm::ivec3;
    using Vector4i = glm::ivec4;

    //===============================================================================================================================
    //  Vectors Unsigned Int
    //===============================================================================================================================
    using Vector2u = glm::uvec2;
    using Vector3u = glm::uvec3;
    using Vector4u = glm::uvec4;

    //===============================================================================================================================
    //  Matrix
    //===============================================================================================================================
    using Matrix3 = glm::mat3;
    using Matrix4 = glm::mat4;

    //===============================================================================================================================
    //  Quaternion
    //===============================================================================================================================
    using Quaternion = glm::quat;

    //===============================================================================================================================
    //  Color
    //===============================================================================================================================
    struct Color : public glm::vec4
    {
        using glm::vec4::vec4;

        static Color White;
        static Color Black;
        static Color Gray;
        static Color Red;
        static Color Green;
        static Color Blue;
        static Color Magenta;
        static Color Yellow;
        static Color Transparent;
    };

    inline Color Color::Red{ 1.0f, 0.0f, 0.0f, 1.0f };
    inline Color Color::White{ 1.0f, 1.0f, 1.0f, 1.0f };
    inline Color Color::Black{ 0.0f, 0.0f, 0.0f, 1.0f };
    inline Color Color::Gray{ 0.5f, 0.5f, 0.5f, 1.0f };
    inline Color Color::Green{ 0.0f, 1.0f, 0.0f, 1.0f };
    inline Color Color::Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
    inline Color Color::Magenta{ 1.0f, 0.0f, 1.0f, 1.0f };
    inline Color Color::Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
    inline Color Color::Transparent{ 0.0f, 0.0f, 0.0f, 0.0f };
}
