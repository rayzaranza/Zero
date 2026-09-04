#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Layer/LayerStack.h"
#include "UI/UILayer.h"
#include "Window/Window.h"

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
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        Window& GetWindow() const;
        static Application& Get();

      private:
        bool onWindowClosed(WindowClosedEvent& event);

      private:
        std::unique_ptr<Window> m_Window {};
        bool m_IsRunning {};
        LayerStack m_LayerStack {};
        UILayer* m_UILayer {};

      private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}
