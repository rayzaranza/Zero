#pragma once
#include "SceneCamera.h"
#include "ScriptableEntity.h"

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
  SceneCamera Camera{};
  bool IsMain{ true };
  bool IsAspectRatioFixed{ false };
  CameraComponent() = default;
  CameraComponent(const CameraComponent&) = default;
};

struct NativeScriptComponent {
  ScriptableEntity* Instance{ nullptr };
  std::function<void()> InstantiateFunction;
  std::function<void()> DestroyInstanceFunction;
  std::function<void(ScriptableEntity*)> OnCreateFunction;
  std::function<void(ScriptableEntity*)> OnDestroyFunction;
  std::function<void(ScriptableEntity*, const DeltaTime)> OnUpdateFunction;
  template <typename T> void Bind();
};

}

template <typename T>
void Zero::NativeScriptComponent::Bind() {
  InstantiateFunction = [&]() { Instance = new T(); };
  DestroyInstanceFunction = [&]() {
    delete (T*)Instance;
    Instance = nullptr;
  };
  OnCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
  OnDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
  OnUpdateFunction = [](ScriptableEntity* instance, const DeltaTime deltaTime) { ((T*)instance)->OnUpdate(deltaTime); };
}
