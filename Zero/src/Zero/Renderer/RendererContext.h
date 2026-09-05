#pragma once

namespace Zero
{
    class RendererContext
    {
      public:
        virtual void Initialize() = 0;
        virtual void SwapBuffers() = 0;
    };
}
