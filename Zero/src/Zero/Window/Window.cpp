#include "Zero/Window/Window.h"

#include <GLFW/glfw3.h>

#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/KeyEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Renderer/OpenGL/OpenGLContext.h"

namespace Zero
{
    static void sendWindowToSecondMonitor(GLFWwindow* window, int width, int height);

    Window::Window(const std::string& title, int width, int height) : m_Data{title, width, height}
    {
        Initialize();
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::Initialize()
    {
        ZERO_CORE_LOG("Window created: {} ({}, {})", m_Data.Title, m_Data.Width, m_Data.Height);

        int glfwInitSuccess{glfwInit()};
        ZERO_CORE_ASSERT(glfwInitSuccess, "Failed to initialize GLFW");
        glfwSetErrorCallback(errorCallback);

        int monitorCount;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
        m_WindowHandle = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

        m_RendererContext = new OpenGLContext(m_WindowHandle);
        m_RendererContext->Initialize();

        glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
        glfwSwapInterval(1);

        setCallbacks();
        sendWindowToSecondMonitor(m_WindowHandle, m_Data.Width, m_Data.Height);
    }

    void Window::Destroy()
    {
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    }

    void Window::setCallbacks()
    {
        glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            data.Width = width;
            data.Height = height;
            WindowResizedEvent event{width, height};
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            WindowClosedEvent event;
            data.EventCallback(event);
        });

        glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            MouseScrolledEvent event{static_cast<float>(xOffset), static_cast<float>(yOffset)};
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double x, double y) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            MouseMovedEvent event{static_cast<float>(x), static_cast<float>(y)};
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event{key, 0};
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event{key};
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event{key, 1};
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, unsigned int keyCode) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            KeyTypedEvent event{static_cast<int>(keyCode)};
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data{*(WindowData*)glfwGetWindowUserPointer(window)};
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event{button};
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event{button};
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

    void sendWindowToSecondMonitor(GLFWwindow* window, int width, int height)
    {
        int monitorCount;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
        GLFWmonitor* monitor{monitors[1]};
        const GLFWvidmode* mode{glfwGetVideoMode(monitor)};
        int x, y;
        glfwGetMonitorPos(monitor, &x, &y);
        glfwSetWindowPos(window, x + (mode->width - width) / 2, y + (mode->height - height) / 2 - 24);
    }
}
