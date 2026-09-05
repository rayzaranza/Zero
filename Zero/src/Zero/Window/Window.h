#pragma once

#include "Zero/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Zero
{
    using EventCallback = std::function<void(Event&)>;

    struct WindowData
    {
        std::string Title {};
        unsigned int Width {};
        unsigned int Height {};
        EventCallback EventCallback {};
    };

    class Window
    {
      public:
        Window(const std::string& title = "ZERO", unsigned int width = 1800, unsigned int height = 940);
        ~Window();

      public:
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        GLFWwindow* GetWindowHandle() const;
        void SetEventCallback(const EventCallback& callback);
        void OnUpdate();
        void Initialize();
        void Destroy();

      private:
        GLFWwindow* m_WindowHandle {};
        RendererContext* m_RendererContext {};
        WindowData m_Data {};

      private:
        void setCallbacks();
    };
}
