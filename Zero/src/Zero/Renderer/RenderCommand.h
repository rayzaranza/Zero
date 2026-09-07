#pragma once

#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class RenderCommand
    {
      public:
        static void Clear();
        static void SetClearColor(const glm::vec4& color);
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

      private:
        static RendererAPI* s_RendererAPI;
    };
}
