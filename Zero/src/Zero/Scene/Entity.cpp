#include "Entity.h"
#include <entt/entt.hpp>

Zero::Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle{ handle }, m_Scene{ scene } {
}

Zero::Entity::operator bool() const {
  return m_EntityHandle != entt::null;
}

Zero::Entity::operator uint32_t() const {
  return static_cast<uint32_t>(m_EntityHandle);
}

bool Zero::Entity::operator==(const Entity& entity) const {
  return m_EntityHandle == entity.m_EntityHandle && m_Scene == entity.m_Scene;
}

bool Zero::Entity::operator!=(const Entity& entity) const {
  return !operator==(entity);
}
