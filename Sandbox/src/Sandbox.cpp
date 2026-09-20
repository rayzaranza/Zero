#include "Sandbox.h"
#include "Sandbox2D.h"
#include <Zero/Core/EntryPoint.h>

Sandbox::Sandbox() {
  PushLayer(new Sandbox2D());
}

Zero::Application* Zero::CreateApplication() {
  return new Sandbox();
}
