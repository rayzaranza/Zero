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
        static void OnWindowResized(const Vector2u& size);
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(const VertexArrayRef& vertexArray, const ShaderRef& shader, const Matrix4& transform = Matrix4{ 1.0f });
        static void EndScene();

      public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

      private:
        struct SceneData
        {
            Matrix4 ViewProjectionMatrix{ 1.0f };
        };

        static SceneData* s_SceneData;
    };
}
