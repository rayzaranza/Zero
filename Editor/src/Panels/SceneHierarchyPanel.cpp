#include "SceneHierarchyPanel.h"
#include <entt/entt.hpp>
#include <imgui.h>

Zero::SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) : m_Context{ context } {
}

void Zero::SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
  m_Context = context;
}

void Zero::SceneHierarchyPanel::OnUIRender() {
  ImGui::Begin("Scene Hierarchy");

  for (entt::entity entityID : m_Context->m_Registry.view<TagComponent>()) {
    const Entity entity{ entityID, m_Context.get() };
    DrawEntityNode(entity);
  }

  if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
    m_SelectedEntity = {};
  }

  ImGui::End();

  ImGui::Begin("Properties");
  if (m_SelectedEntity) {
    DrawComponents(m_SelectedEntity);
  }
  ImGui::End();
}

void Zero::SceneHierarchyPanel::DrawEntityNode(Entity entity) {
  const std::string& tag{ entity.GetComponent<TagComponent>().Tag };
  const ImGuiTreeNodeFlags flags{ ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow };
  const bool isExpanded{ ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str()) };
  if (ImGui::IsItemClicked()) {
    m_SelectedEntity = entity;
  }
  if (isExpanded) {
    ImGui::TreePop();
  }
}

void Zero::SceneHierarchyPanel::DrawComponents(Entity entity) {
  if (entity.HasComponent<TagComponent>()) {
    std::string& tag{ entity.GetComponent<TagComponent>().Tag };
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strcpy_s(buffer, sizeof(buffer), tag.c_str());
    if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
      tag = std::string(buffer);
    }
  }

  if (entity.HasComponent<TransformComponent>()) {
    if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
      glm::mat4& transform{ entity.GetComponent<TransformComponent>().Transform };
      ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
      ImGui::TreePop();
    }
  }

  if (entity.HasComponent<CameraComponent>()) {
    if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")) {
      CameraComponent& cameraComponent{ entity.GetComponent<CameraComponent>() };
      SceneCamera& camera{ cameraComponent.Camera };

      ImGui::Checkbox("Main Camera", &cameraComponent.IsMain);

      const char* projectionTypeStrings[]{ "Perspective", "Orthographic" };
      const char* currentProjectionTypeString{ projectionTypeStrings[static_cast<int>(camera.GetProjectionType())] };

      if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
        for (int i{ 0 }; i < 2; ++i) {
          bool isSelected{ currentProjectionTypeString == projectionTypeStrings[i] };
          if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
            currentProjectionTypeString = projectionTypeStrings[i];
            camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
          }
          if (isSelected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
        float perspectiveVerticalFOV{ glm::degrees(camera.GetPerspectiveVerticalFOV()) };
        if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFOV)) {
          camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFOV));
        }
        float perspectiveNearClip{ camera.GetPerspectiveNearClip() };
        if (ImGui::DragFloat("Near", &perspectiveNearClip)) {
          camera.SetPerspectiveNearClip(perspectiveNearClip);
        }
        float perspectiveFarClip{ camera.GetPerspectiveFarClip() };
        if (ImGui::DragFloat("Far", &perspectiveFarClip)) {
          camera.SetPerspectiveFarClip(perspectiveFarClip);
        }
      }

      if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
        float orthographicSize{ camera.GetOrthographicSize() };
        if (ImGui::DragFloat("Size", &orthographicSize)) {
          camera.SetOrthographicSize(orthographicSize);
        }
        float orthographicNearClip{ camera.GetOrthographicNearClip() };
        if (ImGui::DragFloat("Near", &orthographicNearClip)) {
          camera.SetOrthographicNearClip(orthographicNearClip);
        }
        float orthographicFarClip{ camera.GetOrthographicFarClip() };
        if (ImGui::DragFloat("Far", &orthographicFarClip)) {
          camera.SetOrthographicFarClip(orthographicFarClip);
        }

        ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.IsAspectRatioFixed);
      }

      ImGui::TreePop();
    }
  }

  if (entity.HasComponent<SpriteComponent>()) {
    if (ImGui::TreeNodeEx((void*)typeid(SpriteComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite")) {
      SpriteComponent& spriteComponent{ entity.GetComponent<SpriteComponent>() };
      ImGui::ColorEdit4("Color", glm::value_ptr(spriteComponent.Color));
      ImGui::TreePop();
    }
  }
}
