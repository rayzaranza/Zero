#include "EditorLayer.h"
#include <Zero.h>
#include <Zero/Core/EntryPoint.h>

namespace Zero {
  class Editor : public Application {
  public:
    Editor() : Application{ "Zero Editor" } { PushLayer(new EditorLayer()); }
  };

  Application* CreateApplication() {
    return new Editor();
  }
}
