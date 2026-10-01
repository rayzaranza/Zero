#pragma once
#include <Zero.h>


namespace Zero {


class SceneHierarchyPanel
{
  public:
    SceneHierarchyPanel() = default;
    SceneHierarchyPanel(const Ref<Scene>& context);

  public:
    void SetContext(const Ref<Scene>& context);
    void OnUIRender();
    void DrawEntityNode(Entity entity);
    void DrawComponents(Entity entity);
    Entity GetSelectedEntity() const;

  private:
    void DrawPropertiesPanel();
    void DrawSceneHierarchyPanel();

  private:
    Ref<Scene> m_Context;
    Entity m_SelectionContext;
};


}
