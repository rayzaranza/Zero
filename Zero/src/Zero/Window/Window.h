#pragma once

#include "Zero/Core/Core.h"
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
        Vector2i Size{};
        EventCallback EventCallback{};
    };

    //=====================================================================================================================================
    //  Window
    //=====================================================================================================================================
    class Window
    {
      public:
        Window(const String& title = "ZERO", const Vector2i& size = Vector2i{ 1280, 720 });
        ~Window();

      public:
        inline const Vector2i& GetSize() const { return m_Data.Size; }
        inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
        inline void SetEventCallback(const EventCallback& callback) { m_Data.EventCallback = callback; }
        inline F32 GetAspectRatio() const { return static_cast<F32>(m_Data.Size.x) / static_cast<F32>(m_Data.Size.y); }

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
        inline static void errorCallback(const I32 error, const char* description) { ZR_CORE_ERROR("GLFW Error ({}): {}", error, description); }
    };
}
