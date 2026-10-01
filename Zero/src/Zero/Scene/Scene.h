#pragma once
#include "Zero/Time/DeltaTime.h"
#include <entt/entt.hpp>


namespace Zero {


class Entity;


class Scene
{
  public:
    Scene();
    ~Scene();

  public:
    void OnUpdate(const DeltaTime deltaTime);
    void OnRender();
    void OnViewportResize(const glm::uvec2& size);
    Entity CreateEntity(const std::string& name = "Entity");
    void DestroyEntity(Entity entity);
    Entity GetMainCameraEntity();

  private:
    entt::registry m_Registry;
    glm::uvec2 m_ViewportSize{ 0u };
    friend class Entity;
    friend class SceneSerializer;
    friend class SceneHierarchyPanel;
};


}
