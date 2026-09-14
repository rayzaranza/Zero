#include "Zero/Math/Math.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    glm::mat4 CalculcateModelMatrix(const glm::vec3& position, const Radians rotation, const glm::vec3& scale)
    {
        ZR_PROFILE_FUNCTION();

        glm::mat4 modelMatrix{ 1.0f };

        if (position != glm::vec3{ 0.0f })
            modelMatrix = glm::translate(modelMatrix, position);

        if (rotation != 0.0f)
            modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3{ 0.0f, 0.0f, 1.0f });

        if (scale != glm::vec3{ 1.0f })
            modelMatrix = glm::scale(modelMatrix, scale);

        return modelMatrix;
    }

    glm::mat4 CalculcateModelMatrix2D(const glm::vec2& position, const Radians rotation, const glm::vec2& scale)
    {
        return CalculcateModelMatrix(glm::vec3{ position, 0.0f }, rotation, glm::vec3{ scale, 1.0f });
    }
}
