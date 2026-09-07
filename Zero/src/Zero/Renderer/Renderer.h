#pragma once

#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class Renderer
    {
      public:
        static void BeginScene();
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

      public:
        static RendererAPI::API GetAPI();
    };
}
