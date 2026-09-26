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
      ImGui::DragFloat2("Position", glm::value_ptr(transform[3]), 0.1f);
      ImGui::TreePop();
    }
  }
}
