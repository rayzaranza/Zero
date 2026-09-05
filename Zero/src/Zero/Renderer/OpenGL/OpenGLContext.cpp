#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Zero
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle { windowHandle }
    {
        ZERO_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    OpenGLContext::~OpenGLContext()
    {}

    void OpenGLContext::Initialize()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int gladLoadSuccess { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        ZERO_CORE_ASSERT(gladLoadSuccess, "Failed to load GLAD");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
