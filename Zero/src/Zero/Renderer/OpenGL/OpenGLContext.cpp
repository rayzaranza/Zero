#include "Zero/Renderer/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Zero
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle{ windowHandle }
    {
        ZR_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    OpenGLContext::~OpenGLContext()
    {}

    void OpenGLContext::Initialize()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int gladLoadSuccess{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        ZR_CORE_ASSERT(gladLoadSuccess, "Failed to load GLAD");

        ZR_CORE_INFO("OpenGL Context:");
        ZR_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
        ZR_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
        ZR_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));

        ZERO_CORE_INFO("OpenGL Context:");
        ZERO_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
        ZERO_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
        ZERO_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
