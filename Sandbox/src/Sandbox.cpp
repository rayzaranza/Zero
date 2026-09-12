#include "Sandbox.h"

#include <Zero/Core/EntryPoint.h>

#include "Layers/ExampleLayer.h"
#include "Layers/ExampleLayer2D.h"

Sandbox::Sandbox()
{
    // PushLayer(new ExampleLayer());
    PushLayer(new ExampleLayer2D());
}

Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
