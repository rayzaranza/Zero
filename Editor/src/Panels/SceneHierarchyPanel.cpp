#include "SceneHierarchyPanel.h"
#include <entt/entt.hpp>
#include <imgui.h>
#include <imgui_internal.h>


Zero::SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) : m_Context{ context } {
}


void Zero::SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
  m_Context = context;
}


static void
DrawVector3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f) {
  ImGui::PushID(label.c_str());
  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();
  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });
  const float lineHeight{ GImGui->FontSize + GImGui->Style.FramePadding.y * 2.0f };
  const ImVec2 buttonSize{ lineHeight + 3.0f, lineHeight };

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f, 0.08f, 0.12f, 1.0f });

  if (ImGui::Button("X", buttonSize)) {
    values.x = resetValue;
  }

  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.4f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.62f, 0.2f, 1.0f });

  if (ImGui::Button("Y", buttonSize)) {
    values.y = resetValue;
  }

  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.18f, 0.7f, 1.0f });

  if (ImGui::Button("Z", buttonSize)) {
    values.z = resetValue;
  }

  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();
  ImGui::Columns(1);
  ImGui::PopID();
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

  if (ImGui::BeginPopupContextWindow(0, 1 | ImGuiPopupFlags_NoOpenOverItems)) {
    if (ImGui::MenuItem("Create Empty Entity")) {
      m_Context->CreateEntity("Empty Entity");
    }
    ImGui::EndPopup();
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
  const ImGuiTreeNodeFlags selectedFlag{ m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0 };
  const ImGuiTreeNodeFlags flags{ selectedFlag | ImGuiTreeNodeFlags_OpenOnArrow };
  const bool isExpanded{ ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str()) };

  if (ImGui::IsItemClicked()) {
    m_SelectedEntity = entity;
  }

  if (ImGui::BeginPopupContextItem()) {
    if (ImGui::MenuItem("Destroy Entity")) {
      m_Context->DestroyEntity(entity);
    }
    ImGui::EndPopup();
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
      TransformComponent& transform{ entity.GetComponent<TransformComponent>() };
      DrawVector3Control("Translation", transform.Translation);
      glm::vec3 rotation{ glm::degrees(transform.Rotation) };
      DrawVector3Control("Rotation", rotation);
      transform.Rotation = glm::radians(rotation);
      DrawVector3Control("Scale", transform.Scale, 1.0f);
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
