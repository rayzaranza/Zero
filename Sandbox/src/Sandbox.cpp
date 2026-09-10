#include "Sandbox.h"

#include <imgui.h>

#include <Zero/Renderer/OpenGL/OpenGLShader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
    : Zero::Layer{ "Example" }
    , m_Camera{ -1.6f, 1.6f, -0.9f, 0.9f }
    , m_CameraPosition{ 0.0f }
    , m_CameraMovementSpeed{ 1.0f }
    , m_CameraRotationSpeed{ 90.0f }
    , m_CameraRotation{ 0.0f }
    , m_QuadPosition{ 0.0f }
    , m_QuadMovementSpeed{ 1.0f }
    , m_QuadColor{ 1.0f, 0.0f, 0.0f, 1.0f }
    , m_Texture{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg") }
    , m_TransparentTexture{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/zzz.png") }
    , m_QuadShader{ Zero::Shader::Create("D:/Zero/Sandbox/assets/shaders/Flat.glsl") }
    , m_ShaderLibrary{ std::make_shared<Zero::ShaderLibrary>() }
{
    Zero::VertexBufferLayout layout{
        { Zero::AttributeType::Float3, "a_Position" },
        { Zero::AttributeType::Float2, "a_UV" },
    };

    float quadVertices[]{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, //
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, //
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, //
    };

    uint32_t quadIndices[]{ 0, 1, 2, 2, 3, 0 };

    m_QuadVertexArray.reset(Zero::VertexArray::Create());

    Zero::Ref<Zero::VertexBuffer> quadVertexBuffer{ Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)) };
    quadVertexBuffer->SetLayout(layout);
    m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

    Zero::Ref<Zero::IndexBuffer> quadIndexBuffer{ Zero::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)) };
    m_QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

    m_ShaderLibrary->Load("D:/Zero/Sandbox/assets/shaders/Texture.glsl");

    Zero::Ref<Zero::OpenGLShader> textureShader{ std::dynamic_pointer_cast<Zero::OpenGLShader>(m_ShaderLibrary->Get("Texture")) };
    textureShader->Bind();
    textureShader->SetUniform("u_Texture", 0);
}

void ExampleLayer::OnUpdate(Zero::DeltaTime deltaTime)
{
    if (Zero::Input::IsKeyPressed(Zero::Key::D))
        m_CameraPosition.x += m_CameraMovementSpeed * deltaTime;
    else if (Zero::Input::IsKeyPressed(Zero::Key::A))
        m_CameraPosition.x -= m_CameraMovementSpeed * deltaTime;

    if (Zero::Input::IsKeyPressed(Zero::Key::W))
        m_CameraPosition.y += m_CameraMovementSpeed * deltaTime;
    else if (Zero::Input::IsKeyPressed(Zero::Key::S))
        m_CameraPosition.y -= m_CameraMovementSpeed * deltaTime;

    if (Zero::Input::IsKeyPressed(Zero::Key::Q))
        m_CameraRotation += m_CameraRotationSpeed * deltaTime;
    else if (Zero::Input::IsKeyPressed(Zero::Key::E))
        m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    glm::mat4 triangleModelMatrix{ 1.0f };

    Zero::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Zero::RenderCommand::Clear();

    Zero::Renderer::BeginScene(m_Camera);
    {
        std::dynamic_pointer_cast<Zero::OpenGLShader>(m_QuadShader)->Bind();
        std::dynamic_pointer_cast<Zero::OpenGLShader>(m_QuadShader)->SetUniform("u_Color", m_QuadColor);

        for (int y{ 0 }; y < 20; ++y)
        {
            for (int x{ 0 }; x < 20; ++x)
            {
                glm::vec3 position{ static_cast<float>(x) * 0.11f, static_cast<float>(y) * 0.11f, 0.0f };
                glm::mat4 quadModelMatrix{ glm::translate({ 1.0f }, position) * glm::scale({ 1.0f }, glm::vec3{ 0.1f }) };
                Zero::Renderer::Submit(m_QuadVertexArray, m_QuadShader, quadModelMatrix);
            }
        }

        m_Texture->Bind();

        Zero::Ref<Zero::OpenGLShader> textureShader{ std::dynamic_pointer_cast<Zero::OpenGLShader>(m_ShaderLibrary->Get("Texture")) };
        Zero::Renderer::Submit(m_QuadVertexArray, textureShader);
        m_TransparentTexture->Bind();

        glm::mat4 transparentQuadTransform{ glm::translate({ 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f }) *
                                            glm::scale({ 1.0f }, glm::vec3{ 0.25f }) };
        Zero::Renderer::Submit(m_QuadVertexArray, textureShader);
    }
    Zero::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Zero::Event& event)
{}

void ExampleLayer::OnUIRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_QuadColor));
    ImGui::End();
}
