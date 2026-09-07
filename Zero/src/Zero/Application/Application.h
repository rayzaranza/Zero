#pragma once

#include "Zero/Core.h"
#include "Zero/Event/Event.h"
#include "Zero/Layer/LayerStack.h"
#include "Zero/Renderer/Buffer.h"
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
        bool OnWindowClosed(WindowClosedEvent& event);

      private:
        std::unique_ptr<Window> m_Window {};
        bool m_IsRunning {};
        LayerStack m_LayerStack {};
        UILayer* m_UILayer {};

        unsigned int m_VertexArray {};
        std::unique_ptr<IndexBuffer> m_IndexBuffer {};
        std::unique_ptr<VertexBuffer> m_VertexBuffer {};
        std::unique_ptr<Shader> m_Shader {};

      private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}
