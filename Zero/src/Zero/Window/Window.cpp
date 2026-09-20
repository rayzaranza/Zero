#include "Window.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/KeyEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Renderer/GraphicsContext.OpenGL.h"
#include <GLFW/glfw3.h>

static void SendWindowToSecondMonitor(GLFWwindow* window, const glm::ivec2& size);

Zero::Window::Window(const std::string& title, const glm::ivec2& size) : m_Data{ title, size } {
  Initialize();
}

Zero::Window::~Window() {
  Destroy();
}

const glm::ivec2& Zero::Window::GetSize() const {
  return m_Data.Size;
}

GLFWwindow* Zero::Window::GetWindowHandle() const {
  return m_WindowHandle;
}

void Zero::Window::SetEventCallback(const EventCallback& callback) {
  m_Data.EventCallback = callback;
}

float Zero::Window::GetAspectRatio() const {
  return static_cast<float>(m_Data.Size.x) / static_cast<float>(m_Data.Size.y);
}

void Zero::Window::Initialize() {
  const int32_t glfwInitSuccess{ glfwInit() };
  ZR_CORE_ASSERT(glfwInitSuccess, "Failed to initialize GLFW");
  glfwSetErrorCallback(ErrorCallback);

  int32_t monitorCount{};
  GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

  m_WindowHandle = glfwCreateWindow(m_Data.Size.x, m_Data.Size.y, m_Data.Title.c_str(), nullptr, nullptr);

  m_RendererContext = new GraphicsContextOpenGL(m_WindowHandle);
  m_RendererContext->Initialize();

  glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
  glfwSwapInterval(0);

  SetCallbacks();
  SendWindowToSecondMonitor(m_WindowHandle, m_Data.Size);
  ZR_CORE_LOG("Window created: {} ({}, {})", m_Data.Title, m_Data.Size.x, m_Data.Size.y);
}

void Zero::Window::Destroy() {
  glfwDestroyWindow(m_WindowHandle);
  glfwTerminate();
}

void Zero::Window::SetCallbacks() {
  glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, const int32_t width, const int32_t height) {
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

  glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, const double xOffset, const double yOffset) {
    WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
    MouseScrolledEvent event{ glm::vec2{ static_cast<float>(xOffset), static_cast<float>(yOffset) } };
    data.EventCallback(event);
  });

  glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, const double x, const double y) {
    WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
    MouseMovedEvent event{ glm::vec2{ static_cast<float>(x), static_cast<float>(y) } };
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, const int32_t key, const int32_t scanCode, const int32_t action, const int32_t mods) {
    WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
    const KeyCode keyCode{ key };

    switch (action) {
      case GLFW_PRESS: {
        KeyPressedEvent event{ keyCode, 0 };
        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        KeyReleasedEvent event{ keyCode };
        data.EventCallback(event);
        break;
      }
      case GLFW_REPEAT: {
        KeyPressedEvent event{ keyCode, 1 };
        data.EventCallback(event);
        break;
      }
    }
  });

  glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, const uint32_t keyCode) {
    WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
    KeyTypedEvent event{ static_cast<KeyCode>(keyCode) };
    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, const int32_t button, const int32_t action, const int32_t mods) {
    WindowData& data{ *(WindowData*)glfwGetWindowUserPointer(window) };
    const MouseButton mouseButton{ static_cast<MouseButton>(button) };
    switch (action) {
      case GLFW_PRESS: {
        MouseButtonPressedEvent event{ mouseButton };
        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        MouseButtonReleasedEvent event{ mouseButton };
        data.EventCallback(event);
        break;
      }
    }
  });
}

void Zero::Window::ErrorCallback(const int32_t error, const char* description) {
  ZR_CORE_ERROR("GLFW Error ({}): {}", error, description);
}

void Zero::Window::OnUpdate() {
  glfwPollEvents();
  m_RendererContext->SwapBuffers();
}

void SendWindowToSecondMonitor(GLFWwindow* window, const glm::ivec2& size) {
  int32_t monitorCount{};
  GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
  GLFWmonitor* monitor{ monitors[1] };
  const GLFWvidmode* mode{ glfwGetVideoMode(monitor) };
  glm::ivec2 position{};
  glfwGetMonitorPos(monitor, &position.x, &position.y);
  glfwSetWindowPos(window, position.x + (mode->width - size.x) / 2, position.y + (mode->height - size.y) / 2 - 24);
}
