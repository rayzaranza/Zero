#include "Scene.h"
#include "Components.h"
#include "Entity.h"
#include "Zero/Renderer/Renderer2D.h"

Zero::Scene::Scene() {
}

Zero::Scene::~Scene() {
}

void Zero::Scene::OnUpdate(const DeltaTime deltaTime) {
  m_Registry.view<NativeScriptComponent>().each([=](auto entity, NativeScriptComponent& nativeScript) {
    if (!nativeScript.Instance) {
      nativeScript.Instance = nativeScript.InstantiateScript();
      nativeScript.Instance->m_Entity = Entity{ entity, this };
      nativeScript.Instance->OnCreate();
    }
    nativeScript.Instance->OnUpdate(deltaTime);
  });
}

void Zero::Scene::OnRender() {
  Camera* cameraMain{ nullptr };
  glm::mat4* cameraTransform{ nullptr };

  for (const auto [entity, transform, camera] : m_Registry.view<TransformComponent, CameraComponent>().each()) {
    if (camera.IsMain) {
      cameraMain = &camera.Camera;
      cameraTransform = &transform.Transform;
      break;
    }
  }

  if (cameraMain) {
    Renderer2D::BeginScene(*cameraMain, *cameraTransform);
    for (const auto [entity, transform, sprite] : m_Registry.view<TransformComponent, SpriteComponent>().each()) {
      Renderer2D::DrawQuad({ transform, sprite.Color });
    }
    Renderer2D::EndScene();
  }
}

void Zero::Scene::OnViewportResize(const glm::uvec2& size) {
  m_ViewportSize = size;
  m_Registry.view<CameraComponent>().each([=](auto entity, CameraComponent& cameraComponent) {
    if (!cameraComponent.IsAspectRatioFixed) {
      cameraComponent.Camera.SetViewportSize(size);
    }
  });
}

Zero::Entity Zero::Scene::CreateEntity(const std::string& name) {
  Entity entity{ m_Registry.create(), this };
  entity.AddComponent<TransformComponent>();
  entity.AddComponent<TagComponent>(name);
  return entity;
}
