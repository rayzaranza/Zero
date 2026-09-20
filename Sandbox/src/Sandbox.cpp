#include "Sandbox.h"
#include "Layers/ExampleLayer.h"
#include "Layers/ExampleLayer2D.h"
#include "Layers/GameLayer.h"
#include "Layers/Sandbox2D.h"
#include <Zero/Core/EntryPoint.h>

Sandbox::Sandbox() {
  PushLayer(new Sandbox2D());
}

Zero::Application* Zero::CreateApplication() {
  return new Sandbox();
}
