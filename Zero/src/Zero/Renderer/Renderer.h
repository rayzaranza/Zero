#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/RendererAPI.h"
#include "Zero/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Zero
{
    class Renderer
    {
      public:
        static void BeginScene(CameraOrthographic& camera);
        static void Submit(
            const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader,
            const glm::mat4& transform
        );
        static void EndScene();

      public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

      private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix { 1.0f };
        };

        static SceneData* s_SceneData;
    };
}
