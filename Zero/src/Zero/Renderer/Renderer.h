#pragma once
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/RendererAPI.h"
#include "Zero/Renderer/Shader/Shader.h"
#include "Zero/Camera/Camera.h"

#include <glm/glm.hpp>


namespace Zero {


class Renderer
{
  private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix{ 1.0f };
    };

  public:
    static RendererAPI::API GetAPI();
    static void Initialize();
    static void Destroy();
    static void OnWindowResized(const glm::uvec2& size);
    static void BeginScene(CameraOrthographic& camera);
    static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4{ 1.0f });
    static void EndScene();

  private:
    static Scope<SceneData> s_SceneData;
};


}
