#pragma once

#include "Zero/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Zero
{
    class OpenGLContext : public RendererContext
    {
      public:
        OpenGLContext(GLFWwindow* windowHandle);
        ~OpenGLContext();

      public:
        virtual void Initialize() override;
        virtual void SwapBuffers() override;

      private:
        GLFWwindow* m_WindowHandle {};
    };
}
