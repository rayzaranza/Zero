#include "Zero/Window/Window.h"

#include <GLFW/glfw3.h>

#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/KeyEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Renderer/OpenGL/OpenGLContext.h"

namespace Zero
{
    static void SendWindowToSecondMonitor(GLFWwindow* window, const Vector2i& size);

    Window::Window(const String& title, const Vector2i& size) : m_Data{ title, size }
    {
        Initialize();
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::Initialize()
    {
        const I32 glfwInitSuccess{ glfwInit() };
        ZR_CORE_ASSERT(glfwInitSuccess, "Failed to initialize GLFW");
        glfwSetErrorCallback(errorCallback);

        I32 monitorCount{};
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
        m_WindowHandle = glfwCreateWindow(m_Data.Size.x, m_Data.Size.y, m_Data.Title.c_str(), nullptr, nullptr);

        m_RendererContext = new OpenGLContext(m_WindowHandle);
        m_RendererContext->Initialize();

        glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
        glfwSwapInterval(1);

        setCallbacks();
        SendWindowToSecondMonitor(m_WindowHandle, m_Data.Size);
        ZR_CORE_LOG("Window created: {} ({}, {})", m_Data.Title, m_Data.Size.x, m_Data.Size.y);
    }

    void Window::Destroy()
    {
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    }

    void Window::setCallbacks()
    {
        glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, const I32 width, const I32 height) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            data.Size.x = width;
            data.Size.y = height;
            WindowResizedEvent event{ data.Size };
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            WindowClosedEvent event;
            data.EventCallback(event);
        });

        glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, const F64 xOffset, const F64 yOffset) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            MouseScrolledEvent event{ Vector2{ static_cast<F32>(xOffset), static_cast<F32>(yOffset) } };
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, const F64 x, const F64 y) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            MouseMovedEvent event{ Vector2{ static_cast<F32>(x), static_cast<F32>(y) } };
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, const I32 key, const I32 scanCode, const I32 action, const I32 mods) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event{ key, 0 };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event{ key };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event{ key, 1 };
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, const U32 keyCode) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            KeyTypedEvent event{ static_cast<I32>(keyCode) };
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, const I32 button, const I32 action, const I32 mods) {
            WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event{ button };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event{ button };
                    data.EventCallback(event);
                    break;
                }
            }
        });
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        m_RendererContext->SwapBuffers();
    }

    void SendWindowToSecondMonitor(GLFWwindow* window, const Vector2i& size)
    {
        I32 monitorCount{};
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
        GLFWmonitor* monitor{ monitors[1] };
        const GLFWvidmode* mode{ glfwGetVideoMode(monitor) };

        Vector2i position{};
        glfwGetMonitorPos(monitor, &position.x, &position.y);
        glfwSetWindowPos(window, position.x + (mode->width - size.x) / 2, position.y + (mode->height - size.y) / 2 - 24);
    }
}
