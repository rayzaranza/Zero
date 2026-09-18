#pragma once

#include "Zero/Core/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Renderer/RendererContext.h"

#include <glm/glm.hpp>

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
        std::string Title{};
        glm::ivec2 Size{};
        EventCallback EventCallback{};
    };

    //=====================================================================================================================================
    //  Window
    //=====================================================================================================================================
    class Window
    {
      public:
        Window(const std::string& title = "ZERO", const glm::ivec2& size = glm::ivec2{ 1280, 720 });
        ~Window();

      public:
        inline const glm::ivec2& GetSize() const { return m_Data.Size; }
        inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
        inline void SetEventCallback(const EventCallback& callback) { m_Data.EventCallback = callback; }
        inline float GetAspectRatio() const { return static_cast<float>(m_Data.Size.x) / static_cast<float>(m_Data.Size.y); }

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
        inline static void errorCallback(const int32_t error, const char* description)
        {
            ZR_CORE_ERROR("GLFW Error ({}): {}", error, description);
        }
    };
}
