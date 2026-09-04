#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Input/Input.h"

#include <glad/glad.h>

namespace Zero
{
    Application* Application::s_Instance { nullptr };

    Application::Application() : m_Window { std::make_unique<Window>() }, m_IsRunning { true }
    {
        ZERO_ASSERT(s_Instance == nullptr, "Application already exists");
        s_Instance = this;
        m_Window->SetEventCallback(ZERO_BIND_FUNCTION(Application::OnEvent));
    }

    Application::~Application()
    {}

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher { event };
        dispatcher.Dispatch<WindowClosedEvent>(ZERO_BIND_FUNCTION(Application::onWindowClosed));

        for (LayerPointerArray::iterator iterator { m_LayerStack.end() }; iterator != m_LayerStack.begin();)
        {
            (*--iterator)->OnEvent(event);
            if (event.IsHandled())
            {
                break;
            }
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    Window& Application::GetWindow() const
    {
        return *m_Window;
    }

    Application& Application::Get()
    {
        return *s_Instance;
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }
}
