#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class Renderer
    {
      public:
        static void BeginScene(const Camera& camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

      public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}
