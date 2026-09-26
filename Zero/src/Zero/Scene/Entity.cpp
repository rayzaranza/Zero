#include "Entity.h"
#include <entt/entt.hpp>

Zero::Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle{ handle }, m_Scene{ scene } {
}

Zero::Entity::operator bool() const {
  return m_EntityHandle != entt::null;
}
