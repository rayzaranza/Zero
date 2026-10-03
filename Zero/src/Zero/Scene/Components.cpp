#include "Zero/Scene/Components.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


Zero::TransformComponent::TransformComponent(const glm::vec3& translation) : Translation{ translation }
{
}


glm::mat4 Zero::TransformComponent::GetTransform() const
{
    const glm::mat4 translation{ glm::translate(glm::mat4{ 1.0f }, Translation) };
    const glm::mat4 rotation{ glm::toMat4(glm::quat{ Rotation }) };
    const glm::mat4 scale{ glm::scale(glm::mat4{ 1.0f }, Scale) };

    return glm::mat4{ translation * rotation * scale };
}


Zero::SpriteComponent::SpriteComponent(const glm::vec4& color) : Color{ color }
{
}


Zero::TagComponent::TagComponent(const std::string& tag) : Tag{ tag }
{
}
