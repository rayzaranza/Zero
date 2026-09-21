#pragma once

namespace Zero {

struct TransformComponent {
public:
  glm::mat4 Transform{ 1.0f };
public:
  TransformComponent() = default;
  TransformComponent(const TransformComponent&) = default;
  TransformComponent(const glm::mat4& transform);
  operator glm::mat4&();
  operator const glm::mat4&() const;
};

struct SpriteComponent {
public:
  glm::vec4 Color{ 1.0f };
public:
  SpriteComponent() = default;
  SpriteComponent(const SpriteComponent&) = default;
  SpriteComponent(const glm::vec4& color);
};

}
