#pragma once

#include <glm/glm.hpp>

namespace Zero
{

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
}
