#include "Components.h"

Zero::TransformComponent::TransformComponent(const glm::mat4& transform) : Transform{ transform } {
}

Zero::TransformComponent::operator glm::mat4&() {
  return Transform;
}

Zero::TransformComponent::operator const glm::mat4&() const {
  return Transform;
}

Zero::SpriteComponent::SpriteComponent(const glm::vec4& color) : Color{ color } {
}

Zero::TagComponent::TagComponent(const std::string& tag) : Tag{ tag } {
}

Zero::CameraComponent::CameraComponent(const glm::mat4& projection) : Camera{ projection } {
}
