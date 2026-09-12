#include "Zero/Math/Math.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
    Matrix4 CalculcateModelMatrix(const Vector3& position, const Degrees rotation, const Vector3& scale)
    {
        Matrix4 modelMatrix{ 1.0f };
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), Vector3::Up);
        modelMatrix = glm::scale(modelMatrix, scale);
        return modelMatrix;
    }

    Matrix4 CalculcateModelMatrix2D(const Vector2& position, const Degrees rotation, const Vector2& scale)
    {
        return CalculcateModelMatrix(Vector3{ position, 0.0f }, rotation, Vector3{ scale, 1.0f });
    }
}
