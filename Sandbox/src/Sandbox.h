#pragma once

#include <Zero.h>

#include "Layers/ExampleLayer.h"
#include "Layers/ExampleLayer2D.h"

class Sandbox : public Zero::Application
{
  public:
    Sandbox() { PushLayer(new ExampleLayer2D()); }

    ~Sandbox() = default;
};
