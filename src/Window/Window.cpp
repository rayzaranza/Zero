#include "Window.h"
#include <print>
#include <GLFW/glfw3.h>


namespace Zero {


static void ErrorCallback(int error, const char* description);


Window::Window(const WindowProps& props) : m_Props { props }
{
    glfwSetErrorCallback(ErrorCallback);

    if (glfwInit() == GLFW_FALSE)
    {
        std::println("Error initializing GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_WindowHandle = glfwCreateWindow(props.Size.x, props.Size.y, props.Title.c_str(), nullptr, nullptr);

    if (m_WindowHandle == nullptr)
    {
        std::println("Error creating GLFW Window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_WindowHandle);
}


Window::~Window()
{
    if (m_WindowHandle != nullptr)
        glfwDestroyWindow(m_WindowHandle);

    glfwTerminate();
}


void Window::Update() const
{
    glfwPollEvents();
    glfwSwapBuffers(m_WindowHandle);
}


void ErrorCallback(int error, const char* description)
{
    std::println("GLFW Error: {0} {1}\n", error, description);
}


} // Zero
