#include "Sandbox.h"
#include "Layers/ExampleLayer.h"
#include "Layers/ExampleLayer2D.h"
#include "Layers/GameLayer.h"
#include <Zero/Core/EntryPoint.h>

Sandbox::Sandbox() {
  PushLayer(new GameLayer());
}

Zero::Application* Zero::CreateApplication() {
  return new Sandbox();
}
