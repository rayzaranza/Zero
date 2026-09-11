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
        const I32 gladLoadSuccess{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        ZR_CORE_ASSERT(gladLoadSuccess, "Failed to load GLAD");

        ZR_CORE_INFO("OpenGL Context:");
        ZR_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
        ZR_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
        ZR_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));

#       ifdef ZR_ENABLE_ASSERTS
        I32 versionMajor;
        I32 versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
        ZR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 6), "Minimum OpenGL version required is 4.6");
#       endif
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
