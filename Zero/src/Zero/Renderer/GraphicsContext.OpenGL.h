#pragma once
#include "GraphicsContext.h"

struct GLFWwindow;

namespace Zero {
  class GraphicsContextOpenGL : public GraphicsContext {
  public:
    GraphicsContextOpenGL(GLFWwindow* windowHandle);
    ~GraphicsContextOpenGL();
    virtual void Initialize() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
  };
}
