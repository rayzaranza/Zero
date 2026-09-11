#pragma once

#include "Zero/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Zero
{
    //======================================================================================
    //  Event Callback Function
    //======================================================================================

    using EventCallback = std::function<void(Event&)>;

    //======================================================================================
    //  Window Data
    //======================================================================================

    struct WindowData
    {
        std::string Title{};
        int Width{};
        int Height{};
        EventCallback EventCallback{};
    };

    //======================================================================================
    //  Window
    //======================================================================================

    class Window
    {
      public:
        Window(const std::string& title = "ZERO", int width = 1280, int height = 720);
        ~Window();

      public:
        inline int GetWidth() const { return m_Data.Width; }
        inline int GetHeight() const { return m_Data.Height; }
        inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
        inline void SetEventCallback(const EventCallback& callback) { m_Data.EventCallback = callback; }
        inline float GetAspectRatio() const { return static_cast<float>(m_Data.Width) / static_cast<float>(m_Data.Height); }

      public:
        void OnUpdate();
        void Initialize();
        void Destroy();

      private:
        GLFWwindow* m_WindowHandle;
        RendererContext* m_RendererContext;
        WindowData m_Data;

      private:
        void setCallbacks();
        inline static void errorCallback(int error, const char* description) { ZERO_CORE_ERROR("GLFW Error ({}): {}", error, description); }
    };
}
