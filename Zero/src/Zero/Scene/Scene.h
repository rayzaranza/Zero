#pragma once
#include "Zero/Time/DeltaTime.h"
#include <entt/entt.hpp>

namespace Zero {

class Entity;

class Scene {
public:
  Scene();
  ~Scene();
  void OnUpdate(const DeltaTime deltaTime);
  void OnRender();
  void OnViewportResize(const glm::uvec2& size);
  Entity CreateEntity(const std::string& name = "Entity");
private:
  entt::registry m_Registry;
  friend class Entity;
  glm::uvec2 m_ViewportSize{ 0u };
};

}
