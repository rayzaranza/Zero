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
        static void Initialize();
        static void Destroy();
        static void OnWindowResized(const glm::uvec2& size);
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(const VertexArrayRef& vertexArray, const ShaderRef& shader, const glm::mat4& transform = glm::mat4{ 1.0f });
        static void EndScene();

      public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

      private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix{ 1.0f };
        };

        static Scope<SceneData> s_SceneData;
    };
}
