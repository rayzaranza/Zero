#include "Components.h"
#include <glm/gtc/matrix_transform.hpp>


Zero::TransformComponent::TransformComponent(const glm::vec3& translation) : Translation{ translation } {
}


glm::mat4 Zero::TransformComponent::GetTransform() const {
  glm::mat4 transform{ 1.0f };
  transform = glm::translate(transform, Translation);
  transform = glm::rotate(transform, Rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f });
  transform = glm::rotate(transform, Rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f });
  transform = glm::rotate(transform, Rotation.z, glm::vec3{ 0.0f, 0.0f, 1.0f });
  transform = glm::scale(transform, Scale);
  return transform;
}


Zero::SpriteComponent::SpriteComponent(const glm::vec4& color) : Color{ color } {
}


Zero::TagComponent::TagComponent(const std::string& tag) : Tag{ tag } {
}
