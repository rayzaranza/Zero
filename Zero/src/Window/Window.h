#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Zero
{

    class ZERO_API Window
    {
      public:
        using EventCallback = std::function<void(Event&)>;

      public:
        Window(const std::string& title = "ZERO", unsigned int width = 1280, unsigned int height = 720);
        ~Window();

      public:
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        void SetEventCallback(const EventCallback& callback);
        void OnUpdate();
        void Initialize();
        void Destroy();

      private:
        struct WindowData
        {
            std::string Title {};
            unsigned int Width {};
            unsigned int Height {};
            EventCallback EventCallback {};
        };

        GLFWwindow* m_Window {};
        WindowData m_Data {};

      private:
        void setCallbacks();
    };
}
