#include "Zero/Application/Application.h"

#include <GLFW/glfw3.h>

#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Input/Input.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    Application* Application::s_Instance{ nullptr };

    Application::Application()
        : m_Window{ std::make_unique<Window>() }
        , m_UILayer{ new UILayer() }
        , m_IsRunning{ true }
        , m_IsMinimized{ false }
        , m_LastFrameTime{ 0.0f }
    {
        ZR_CORE_ASSERT(s_Instance == nullptr, "Application already exists");
        s_Instance = this;
        m_Window->SetEventCallback(ZR_BIND_FUNCTION(Application::OnEvent));
        PushOverlay(m_UILayer);
        Renderer::Initialize();
    }

    Application::~Application()
    {
        ZR_CORE_LOG("Application destroyed");
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher{ event };
        dispatcher.Dispatch<WindowClosedEvent>(ZR_BIND_FUNCTION(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizedEvent>(ZR_BIND_FUNCTION(Application::OnWindowResized));

        for (Array<Layer*>::iterator iterator{ m_LayerStack.end() }; iterator != m_LayerStack.begin();)
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

    void Application::Close()
    {
        m_IsRunning = false;
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            const Seconds time = static_cast<Seconds>(glfwGetTime());
            DeltaTime deltaTime{ time - m_LastFrameTime };
            m_LastFrameTime = time;

            if (!m_IsMinimized)
            {
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnUpdate(deltaTime);
                    layer->OnRender();
                }
            }

            m_UILayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnUIRender();
            m_UILayer->End();

            m_Window->OnUpdate();
        }
    }

    Boolean Application::OnWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }

    Boolean Application::OnWindowResized(WindowResizedEvent& event)
    {
        const Vector2i size{ event.GetSize() };

        if (size.x == 0 || size.y == 0)
        {
            m_IsMinimized = true;
            return false;
        }

        Renderer::OnWindowResized(size);

        m_IsMinimized = false;
        return false;
    }
}
