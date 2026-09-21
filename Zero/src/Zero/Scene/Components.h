#pragma once
#include "Zero/Camera/Camera.h"

namespace Zero {

struct TagComponent {
  std::string Tag{};
  TagComponent() = default;
  TagComponent(const TagComponent&) = default;
  TagComponent(const std::string& tag);
};

struct TransformComponent {
  glm::mat4 Transform{ 1.0f };
  TransformComponent() = default;
  TransformComponent(const TransformComponent&) = default;
  TransformComponent(const glm::mat4& transform);
  operator const glm::mat4&() const;
  operator glm::mat4&();
};

struct SpriteComponent {
  glm::vec4 Color{ 1.0f };
  SpriteComponent() = default;
  SpriteComponent(const SpriteComponent&) = default;
  SpriteComponent(const glm::vec4& color);
};

struct CameraComponent {
  Camera Camera{};
  bool IsMain{ true };
  CameraComponent() = default;
  CameraComponent(const CameraComponent&) = default;
  CameraComponent(const glm::mat4& projection);
};

}
