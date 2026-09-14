#pragma once

namespace Zero
{
    glm::mat4 CalculcateModelMatrix(const glm::vec3& position, const Radians rotation, const glm::vec3& scale);
    glm::mat4 CalculcateModelMatrix2D(const glm::vec2& position, const Radians rotation, const glm::vec2& scale);
}
