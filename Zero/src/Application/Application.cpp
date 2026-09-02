#include "Application.h"
#include "Events/ApplicationEvent.h"

namespace Zero
{
    Application::Application() : m_Window { std::make_unique<Window>() }, m_IsRunning { true }
    {
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {}

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher { event };
        dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));

        ZERO_CORE_LOG(event);
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }
}
