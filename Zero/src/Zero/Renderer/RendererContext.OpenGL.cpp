#include "RendererContext.OpenGL.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Zero::RendererContextOpenGL::RendererContextOpenGL(GLFWwindow* windowHandle) : m_WindowHandle{ windowHandle } {
  ZR_CORE_ASSERT(windowHandle, "Window handle is null");
}

Zero::RendererContextOpenGL::~RendererContextOpenGL() {
}

void Zero::RendererContextOpenGL::Initialize() {
  glfwMakeContextCurrent(m_WindowHandle);
  const int32_t gladLoadSuccess{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
  ZR_CORE_ASSERT(gladLoadSuccess, "Failed to load GLAD");
  ZR_CORE_INFO("OpenGL {0} | {1}", (char*)glGetString(GL_VERSION), (char*)glGetString(GL_RENDERER));

# ifdef ZR_ENABLE_ASSERTS
  int32_t versionMajor;
  int32_t versionMinor;
  glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
  glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
  ZR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 6), "Minimum OpenGL version required is 4.6");
# endif
}

void Zero::RendererContextOpenGL::SwapBuffers() {
  glfwSwapBuffers(m_WindowHandle);
}
