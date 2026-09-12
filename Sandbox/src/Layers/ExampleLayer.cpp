#include "ExampleLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
    : Zero::Layer{ "Example" }
    , m_QuadPosition{ 0.0f }
    , m_QuadMovementSpeed{ 1.0f }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
    , m_QuadColor{ 1.0f, 0.0f, 0.0f, 1.0f }
{}

void ExampleLayer::OnAttach()
{
    m_ShaderLibrary = Zero::ShaderLibrary::Create();
    m_QuadShader = Zero::Shader::Create("D:/Zero/Sandbox/assets/shaders/Flat.glsl");
    m_Texture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
    m_TransparentTexture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/zzz.png");
    m_QuadVertexArray = Zero::VertexArray::Create();

    const Zero::VertexBufferLayout layout{
        { Zero::AttributeType::Vector3, "a_Position" },
        { Zero::AttributeType::Vector2, "a_UV" },
    };

    const Zero::VertexBufferRef quadVertexBuffer{ Zero::VertexBuffer::Create(
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, //
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, //
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, //
        }
    ) };

    quadVertexBuffer->SetLayout(layout);
    m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

    const Zero::IndexBufferRef quadIndexBuffer{ Zero::IndexBuffer::Create({ 0, 1, 2, 2, 3, 0 }) };
    m_QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

    m_ShaderLibrary->Load("D:/Zero/Sandbox/assets/shaders/Texture.glsl");

    const Zero::ShaderRef textureShader{ m_ShaderLibrary->Get("Texture") };
    textureShader->Bind();
    textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnDetach()
{}

void ExampleLayer::OnUpdate(const Zero::DeltaTime deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);
}

void ExampleLayer::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
}

void ExampleLayer::OnRender()
{
    Zero::RenderCommand::Clear(Zero::Color::Black);
    Zero::Renderer::BeginScene(m_CameraController.GetCamera());

    m_QuadShader->Bind();
    m_QuadShader->SetVector4("u_Color", m_QuadColor);

    for (Zero::I32 y{ 0 }; y < 20; ++y)
    {
        for (Zero::I32 x{ 0 }; x < 20; ++x)
        {
            Zero::Vector3 position{ static_cast<Zero::F32>(x) * 0.11f, static_cast<Zero::F32>(y) * 0.11f, 0.0f };
            Zero::Matrix4 quadModelMatrix{ glm::translate({ 1.0f }, position) * glm::scale({ 1.0f }, Zero::Vector3{ 0.1f }) };
            Zero::Renderer::Submit(m_QuadVertexArray, m_QuadShader, quadModelMatrix);
        }
    }

    m_Texture->Bind();
    const Zero::ShaderRef& textureShader{ m_ShaderLibrary->Get("Texture") };
    Zero::Renderer::Submit(m_QuadVertexArray, textureShader);

    m_TransparentTexture->Bind();
    Zero::Matrix4 transparentQuadTransform{ 1.0f };
    transparentQuadTransform = glm::translate(transparentQuadTransform, Zero::Vector3{ 0.0f, 1.0f, 0.0f });
    transparentQuadTransform = glm::scale(transparentQuadTransform, Zero::Vector3{ 0.25f });
    Zero::Renderer::Submit(m_QuadVertexArray, textureShader);

    Zero::Renderer::EndScene();
}

void ExampleLayer::OnUIRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(static_cast<glm::vec4&>(m_QuadColor)));
    ImGui::End();
}
