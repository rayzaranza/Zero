#pragma once

#include "Zero/Core.h"
#include "Zero/Event/Event.h"
#include "Zero/Layer/LayerStack.h"
#include "Zero/Renderer/Buffer.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/VertexArray.h"
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

      public:
        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }

      private:
        bool OnWindowClosed(WindowClosedEvent& event);

      private:
        std::unique_ptr<Window> m_Window {};
        bool m_IsRunning {};
        LayerStack m_LayerStack {};
        UILayer* m_UILayer {};
        std::shared_ptr<Shader> m_TriangleShader {};
        std::shared_ptr<Shader> m_QuadShader {};
        std::shared_ptr<VertexArray> m_TriangleVertexArray {};
        std::shared_ptr<VertexArray> m_QuadVertexArray {};

      private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}
