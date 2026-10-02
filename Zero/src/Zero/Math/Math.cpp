#include "Zero/Math/Math.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>


glm::mat4 Zero::Math::CalculcateTransform(const glm::vec3& position, const float rotation, const glm::vec3& scale)
{
    glm::mat4 transform{ 1.0f };

    if (position != glm::vec3{ 0.0f })
    {
        transform = glm::translate(transform, position);
    }

    if (rotation != 0.0f)
    {
        transform = glm::rotate(transform, rotation, glm::vec3{ 0.0f, 0.0f, 1.0f });
    }

    if (scale != glm::vec3{ 1.0f })
    {
        transform = glm::scale(transform, scale);
    }

    return transform;
}


glm::mat4 Zero::Math::CalculcateTransform2D(const glm::vec2& position, const float rotation, const glm::vec2& scale)
{
    return CalculcateTransform(glm::vec3{ position, 0.0f }, rotation, glm::vec3{ scale, 1.0f });
}


bool Zero::Math::DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
{
    glm::mat4 localMatrix{ transform };
    constexpr float EPSILON{ glm::epsilon<float>() };

    if (glm::epsilonEqual(localMatrix[3][3], 0.0f, EPSILON))
    {
        return false;
    }

    if (glm::epsilonNotEqual(localMatrix[0][3], 0.0f, EPSILON) || glm::epsilonNotEqual(localMatrix[1][3], 0.0f, EPSILON) ||
        glm::epsilonNotEqual(localMatrix[2][3], 0.0f, EPSILON))
    {
        localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = 0.0f;
        localMatrix[3][3] = 1.0f;
    }

    translation = glm::vec3{ localMatrix[3] };
    localMatrix[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, localMatrix[3].w };

    glm::vec3 row[3]{};

    for (glm::length_t i{ 0 }; i < 3; ++i)
    {
        for (glm::length_t j{ 0 }; j < 3; ++j)
        {
            row[i][j] = localMatrix[i][j];
        }
    }

    scale.x = glm::length(row[0]);
    row[0] = glm::detail::scale(row[0], 1.0f);
    scale.y = glm::length(row[1]);
    row[1] = glm::detail::scale(row[1], 1.0f);
    scale.z = glm::length(row[2]);
    row[2] = glm::detail::scale(row[2], 1.0f);

    rotation.y = asin(-row[0][2]);

    if (glm::cos(rotation.y) != 0.0f)
    {
        rotation.x = atan2(row[1][2], row[2][2]);
        rotation.z = atan2(row[0][1], row[0][0]);
    }
    else
    {
        rotation.x = atan2(-row[2][0], row[1][1]);
        rotation.z = 0.0f;
    }

    return true;
}
