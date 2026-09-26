add_executable(Editor
  "src/Editor.cpp"
  "src/EditorLayer.h"
  "src/EditorLayer.cpp"
  "src/Panels/SceneHierarchyPanel.h"
  "src/Panels/SceneHierarchyPanel.cpp"
)

target_link_libraries(Editor PRIVATE Zero)
