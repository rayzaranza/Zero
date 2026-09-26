#pragma once
#include "Scene.h"
#include <entt/entt.hpp>

namespace Zero {

class Entity {
public:
  Entity() = default;
  Entity(const Entity&) = default;
  Entity(entt::entity handle, Scene* scene);
public:
  template <typename T> bool HasComponent();
  template <typename T> T& GetComponent();
  template <typename T> void RemoveComponent();
  template <typename T, typename... TArgs> T& AddComponent(TArgs&&... args);
  operator bool() const;
private:
  entt::entity m_EntityHandle{ entt::null };
  Scene* m_Scene{ nullptr };
};

}

template <typename T>
bool Zero::Entity::HasComponent() {
  return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
}

template <typename T>
T& Zero::Entity::GetComponent() {
  ZR_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
  return m_Scene->m_Registry.get<T>(m_EntityHandle);
}

template <typename T>
void Zero::Entity::RemoveComponent() {
  ZR_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
  m_Scene->m_Registry.remove<T>(m_EntityHandle);
}

template <typename T, typename... TArgs>
T& Zero::Entity::AddComponent(TArgs&&... args) {
  ZR_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
  return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<TArgs>(args)...);
}
