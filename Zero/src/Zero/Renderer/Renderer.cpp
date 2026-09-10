#include "Zero/Renderer/Renderer.h"

#include "Zero/Renderer/OpenGL/OpenGLShader.h"

namespace Zero
{
    Renderer::SceneData* Renderer::s_SceneData{new Renderer::SceneData()};

    void Renderer::Initialize()
    {
        RenderCommand::Initialize();
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& modelMatrix)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniform("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniform("u_ModelMatrix", modelMatrix);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {}
}
