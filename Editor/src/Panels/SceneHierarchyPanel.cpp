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
  ImGui::End();
}

void Zero::SceneHierarchyPanel::DrawEntityNode(Entity entity) {
  const std::string& tag{ entity.GetComponent<TagComponent>().Tag };
  const ImGuiTreeNodeFlags flags{ ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow };
  const bool isNodeExpanded{ ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str()) };
  if (ImGui::IsItemClicked()) {
    m_SelectionContext = entity;
  }
  if (isNodeExpanded) {
    ImGui::TreePop();
  }
}
