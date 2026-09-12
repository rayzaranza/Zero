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
        inline static void Clear(const Color& color) { s_RendererAPI->Clear(color); }
        inline static void SetViewport(const Vector2i& position, const Vector2u& size) { s_RendererAPI->SetViewport(position, size); }
        inline static void DrawIndexed(const VertexArrayRef& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

      private:
        static RendererAPI* s_RendererAPI;
    };
}
