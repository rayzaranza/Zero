#pragma once

#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class RenderCommand
    {
      public:
        inline static void Initialize() { s_RendererAPI->Initialize(); }
        inline static void Clear() { s_RendererAPI->Clear(); }
        inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
        inline static void SetViewport(int x, int y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

      private:
        static RendererAPI* s_RendererAPI;
    };
}
