#pragma once

#include "Zero/Core.h"
#include "Zero/Event/Event.h"
#include "Zero/Layer/LayerStack.h"
#include "Zero/Renderer/Shader.h"
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
        Window& GetWindow() const;
        static Application& Get();

      private:
        bool onWindowClosed(WindowClosedEvent& event);

      private:
        std::unique_ptr<Window> m_Window {};
        bool m_IsRunning {};
        LayerStack m_LayerStack {};
        UILayer* m_UILayer {};

        unsigned int m_VertexArray {};
        unsigned int m_VertexBuffer {};
        unsigned int m_IndexBuffer {};
        std::unique_ptr<Shader> m_Shader {};

      private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}
