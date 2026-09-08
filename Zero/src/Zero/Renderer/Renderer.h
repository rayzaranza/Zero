#pragma once

#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class Renderer
    {
      public:
        inline static void BeginScene() {};
        inline static void EndScene() {};
        inline static void Submit(const std::shared_ptr<VertexArray>& vertexArray)
        {
            vertexArray->Bind();
            RenderCommand::DrawIndexed(vertexArray);
        }

      public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}
