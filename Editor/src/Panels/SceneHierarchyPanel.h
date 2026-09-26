#pragma once
#include <Zero.h>

namespace Zero {

class SceneHierarchyPanel {
public:
  SceneHierarchyPanel() = default;
  SceneHierarchyPanel(const Ref<Scene>& context);
  void SetContext(const Ref<Scene>& context);
  void OnUIRender();
  void DrawEntityNode(Entity entity);
private:
  Ref<Scene> m_Context;
  Entity m_SelectionContext{};
};

}
