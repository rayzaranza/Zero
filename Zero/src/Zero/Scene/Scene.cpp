#include "Scene.h"
#include "Components.h"
#include "Zero/Renderer/Renderer2D.h"

Zero::Scene::Scene() {
}

Zero::Scene::~Scene() {
}

void Zero::Scene::OnUpdate(const DeltaTime deltaTime) {
}

void Zero::Scene::OnRender() {
  const auto view{ m_Registry.view<TransformComponent, SpriteComponent>() };
  for (const auto [entity, transform, sprite] : view.each()) {
    Renderer2D::DrawQuad({ transform, sprite.Color });
  }
}

entt::entity Zero::Scene::CreateEntity() {
  return m_Registry.create();
}

entt::registry& Zero::Scene::GetRegistry() {
  return m_Registry;
}
