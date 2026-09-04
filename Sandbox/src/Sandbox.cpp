#include <Zero.h>

class ExampleLayer : public Zero::Layer
{
  public:
    ExampleLayer() : Layer { "Example" }
    {}

  public:
    void OnUpdate() override
    {
        if (Zero::Input::IsKeyPressed(ZERO_KEY_TAB))
        {
            ZERO_INFO("Tab key is pressed");
        }
    }

    void OnEvent(Zero::Event& event) override
    {
        if (event.GetEventType() == Zero::EventType::KeyPressed)
        {
            Zero::KeyPressedEvent& e { (Zero::KeyPressedEvent&)event };

            if (e.GetKeyCode() == ZERO_KEY_A)
            {
                ZERO_INFO("A key is pressed");
            }

            ZERO_LOG("{0}", (char)e.GetKeyCode());
        }
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
