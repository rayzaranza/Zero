#pragma once
#include <glm/glm.hpp>


namespace Zero {


class Math
{
  public:
    static glm::mat4 CalculcateTransform(const glm::vec3& position, const float rotation, const glm::vec3& scale);
    static glm::mat4 CalculcateTransform2D(const glm::vec2& position, const float rotation, const glm::vec2& scale);
    static bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale);
};


}
