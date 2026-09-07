#pragma once

namespace Zero
{
    // ················································································································
    //  Renderer Context
    // ················································································································

    class RendererContext
    {
      public:
        virtual void Initialize() = 0;
        virtual void SwapBuffers() = 0;
    };
}
