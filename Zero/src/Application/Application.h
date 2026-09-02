#pragma once

#include "Events/Event.h"
#include "Window/Window.h"
#include "Zero/Core.h"

namespace Zero
{
    class ZERO_API Application
    {
      public:
        Application();
        virtual ~Application();

      public:
        void Run();
        void OnEvent(Event& event);

      private:
        bool onWindowClosed(WindowClosedEvent& event);

      private:
        std::unique_ptr<Window> m_Window {};
        bool m_IsRunning {};
    };

    Application* CreateApplication();
}
