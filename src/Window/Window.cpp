#include "Window.h"
#include "../Logger/Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <utility>


Zero::Window::Window(const WindowProps& props) : m_Props { props }
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        Z_LOG_CRITICAL("Error initializing GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    m_WindowHandle = glfwCreateWindow(props.Size.x, props.Size.y, props.Title.c_str(), nullptr, nullptr);

    if (!m_WindowHandle)
    {
        Z_LOG_CRITICAL("Error creating GLFW Window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_WindowHandle);

    // TODO: Move to renderer
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    Z_LOG("Window created");
}


Zero::Window::~Window()
{
    glfwDestroyWindow(m_WindowHandle);
    glfwTerminate();

    Z_LOG("Window destroyed");
}


void Zero::Window::Update() const
{
    // TODO: move to Renderer
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(m_WindowHandle);
}


Zero::Scope<Zero::Window> Zero::Window::Create(const WindowProps& props)
{
    return CreateScope<Window>(props);
}


void Zero::Window::ErrorCallback(int error, const char* description)
{
    Z_LOG_ERROR("[GLFW Error: {0}] {1}\n", error, description);
}
