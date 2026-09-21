#include "Scene.h"
#include "Components.h"
#include "Entity.h"
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

Zero::Entity Zero::Scene::CreateEntity(const std::string& name) {
  Entity entity{ m_Registry.create(), this };
  entity.AddComponent<TransformComponent>();
  entity.AddComponent<TagComponent>(name);
  return entity;
}
