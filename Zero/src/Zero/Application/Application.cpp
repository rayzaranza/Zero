#include "Zero/Application/Application.h"

#include <GLFW/glfw3.h>

#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Input/Input.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    Application* Application::s_Instance { nullptr };

    Application::Application()
        : m_Window { std::make_unique<Window>() },
          m_UILayer { new UILayer() },
          m_IsRunning { true }
    {
        ZERO_CORE_ASSERT(s_Instance == nullptr, "Application already exists");
        s_Instance = this;
        m_Window->SetEventCallback(ZERO_BIND_FUNCTION(Application::OnEvent));
        PushOverlay(m_UILayer);

        ZERO_CORE_LOG("Application created");
    }

    Application::~Application()
    {
        ZERO_CORE_LOG("Application destroyed");
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher { event };
        dispatcher.Dispatch<WindowClosedEvent>(ZERO_BIND_FUNCTION(Application::OnWindowClosed));

        for (std::vector<Layer*>::iterator iterator { m_LayerStack.end() }; iterator != m_LayerStack.begin();)
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

    void Application::Run()
    {
        while (m_IsRunning)
        {
            float time = static_cast<float>(glfwGetTime());
            DeltaTime deltaTime { time - m_LastFrameTime };
            m_LastFrameTime = time;

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            m_UILayer->Begin();
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUIRender();
            }
            m_UILayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }
}
