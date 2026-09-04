#pragma once

#include "Core.h"
#include "Event/ApplicationEvent.h"

#include <GLFW/glfw3.h>

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

    class ZERO_API Window
    {
      public:
        Window(const std::string& title = "ZERO", unsigned int width = 1800, unsigned int height = 940);
        ~Window();

      public:
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        GLFWwindow* GetGLFWWindow() const;
        void SetEventCallback(const EventCallback& callback);
        void OnUpdate();
        void Initialize();
        void Destroy();

      private:
        GLFWwindow* m_Window {};
        WindowData m_Data {};

      private:
        void setCallbacks();
    };
}
