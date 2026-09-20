#pragma once
#include "RendererContext.h"

struct GLFWwindow;

namespace Zero {
  class RendererContextOpenGL : public RendererContext {
  public:
    RendererContextOpenGL(GLFWwindow* windowHandle);
    ~RendererContextOpenGL();
    virtual void Initialize() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
  };
}
