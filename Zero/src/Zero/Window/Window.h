#pragma once

#include "Zero/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Zero
{
    //=====================================================================================================================================
    //  Event Callback Function
    //=====================================================================================================================================
    using EventCallback = Function<void(Event&)>;

    //=====================================================================================================================================
    //  Window Data
    //=====================================================================================================================================
    struct WindowData
    {
        String Title{};
        I32 Width{};
        I32 Height{};
        EventCallback EventCallback{};
    };

    //=====================================================================================================================================
    //  Window
    //=====================================================================================================================================
    class Window
    {
      public:
        Window(const String& title = "ZERO", I32 width = 1280, I32 height = 720);
        ~Window();

      public:
        inline I32 GetWidth() const { return m_Data.Width; }
        inline I32 GetHeight() const { return m_Data.Height; }
        inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
        inline void SetEventCallback(const EventCallback& callback) { m_Data.EventCallback = callback; }
        inline F32 GetAspectRatio() const { return static_cast<F32>(m_Data.Width) / static_cast<F32>(m_Data.Height); }

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
        inline static void errorCallback(I32 error, const char* description) { ZR_CORE_ERROR("GLFW Error ({}): {}", error, description); }
    };
}
