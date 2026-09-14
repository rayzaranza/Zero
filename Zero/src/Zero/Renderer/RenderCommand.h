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
        inline static void Clear(const glm::vec4& color) { s_RendererAPI->Clear(color); }
        inline static void SetViewport(const glm::ivec2& position, const glm::uvec2& size) { s_RendererAPI->SetViewport(position, size); }
        inline static void DrawIndexed(const VertexArrayRef& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

      private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}
