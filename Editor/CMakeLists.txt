add_executable(Editor
  "src/Editor.cpp"
  "src/EditorLayer.h"
  "src/EditorLayer.cpp"
)

target_link_libraries(Editor PRIVATE Zero)
