#include <Zero/Zero.h>
#include <imgui.h>

class ExampleLayer : public Zero::Layer
{
  public:
    ExampleLayer() : Layer { "Example" }
    {}

  public:
    virtual void OnUpdate() override
    {}

    virtual void OnEvent(Zero::Event& event) override
    {}

    virtual void OnUIRender() override
    {}
};

class Sandbox : public Zero::Application
{
  public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {}
};

Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
