#include <Zero.h>

class ExampleLayer : public Zero::Layer
{
  public:
    ExampleLayer() : Layer { "Example" }
    {}

  public:
    void OnUpdate() override
    {
        ZERO_INFO("ExampleLayer OnUpdate");
    }

    void OnEvent(Zero::Event& event) override
    {
        ZERO_LOG("{0}", event);
    }
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
