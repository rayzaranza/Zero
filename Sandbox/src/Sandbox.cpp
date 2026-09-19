#include "Sandbox.h"

#include <Zero/Core/EntryPoint.h>

#include "Layers/ExampleLayer.h"
#include "Layers/ExampleLayer2D.h"
#include "Layers/GameLayer.h"

Sandbox::Sandbox()
{
    PushLayer(new GameLayer());
}

Zero::Application* Zero::CreateApplication()
{
    ZR_PROFILE_FUNCTION();

    return new Sandbox();
}
