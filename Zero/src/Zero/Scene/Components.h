#pragma once

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
  operator glm::mat4&();
  operator const glm::mat4&() const;
};

struct SpriteComponent {
  glm::vec4 Color{ 1.0f };
  SpriteComponent() = default;
  SpriteComponent(const SpriteComponent&) = default;
  SpriteComponent(const glm::vec4& color);
};

}
