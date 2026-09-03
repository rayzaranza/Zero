#include "Window.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include <glad/glad.h>

namespace Zero
{
    static void errorCallback(int error, const char* description)
    {
        ZERO_CORE_ERROR("GLFW Error ({}): {}", error, description);
    }

    Window::Window(const std::string& title, unsigned int width, unsigned int height) : m_Data { title, width, height }
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

        int glfwInitSuccess { glfwInit() };
        ZERO_CORE_ASSERT(glfwInitSuccess, "Failed to initialize GLFW");
        glfwSetErrorCallback(errorCallback);

        int monitorCount;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), monitors[1], nullptr);
        glfwMakeContextCurrent(m_Window);

        int gladLoadSuccess { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        ZERO_CORE_ASSERT(gladLoadSuccess, "Failed to load GLAD");

        glfwSetWindowUserPointer(m_Window, &m_Data);
        glfwSwapInterval(1);

        setCallbacks();
    }

    void Window::Destroy()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::setCallbacks()
    {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            data.Width = width;
            data.Height = height;
            WindowResizedEvent event { static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            WindowClosedEvent event {};
            data.EventCallback(event);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            MouseScrolledEvent event { static_cast<float>(xOffset), static_cast<float>(yOffset) };
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            MouseMovedEvent event { static_cast<float>(x), static_cast<float>(y) };
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event { key, 0 };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event { key };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event { key, 1 };
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            KeyTypedEvent event { static_cast<int>(keyCode) };
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data { *(WindowData*)glfwGetWindowUserPointer(window) };
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event { button };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event { button };
                    data.EventCallback(event);
                    break;
                }
            }
        });
    }

    unsigned int Window::GetWidth() const
    {
        return m_Data.Width;
    }

    unsigned int Window::GetHeight() const
    {
        return m_Data.Height;
    }

    GLFWwindow* Window::GetGLFWWindow() const
    {
        return m_Window;
    }

    void Window::SetEventCallback(const EventCallback& callback)
    {
        m_Data.EventCallback = callback;
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}
