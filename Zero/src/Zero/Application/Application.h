#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Core/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/Event.h"
#include "Zero/Layer/LayerStack.h"
#include "Zero/Time/DeltaTime.h"
#include "Zero/UI/UILayer.h"
#include "Zero/Window/Window.h"

namespace Zero
{
    class Application
    {
      public:
        Application();
        virtual ~Application();

      public:
        void Run();
        void OnEvent(Event& event);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void Close();

      public:
        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }

      private:
        bool OnWindowClosed(WindowClosedEvent& event);
        bool OnWindowResized(WindowResizedEvent& event);

      private:
        Scope<Window> m_Window;
        bool m_IsRunning;
        bool m_IsMinimized;
        LayerStack m_LayerStack;
        UILayer* m_UILayer;
        Seconds m_LastFrameTime;

      private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}
