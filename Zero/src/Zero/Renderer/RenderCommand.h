#pragma once

#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class RenderCommand
    {
      public:
        inline static void Initialize() { s_RendererAPI->Initialize(); }
        inline static void Clear() { s_RendererAPI->Clear(); }
        inline static void SetClearColor(const Color& color) { s_RendererAPI->SetClearColor(color); }
        inline static void SetViewport(I32 x, I32 y, U32 width, U32 height) { s_RendererAPI->SetViewport(x, y, width, height); }
        inline static void DrawIndexed(const VertexArrayRef& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

      private:
        static RendererAPI* s_RendererAPI;
    };
}
