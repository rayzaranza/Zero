#include "ExampleLayer2D.h"

#include <imgui.h>

#include <Zero/Renderer/OpenGL/OpenGLShader.h>

#include <glm/gtc/type_ptr.hpp>

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_QuadColor{ 1.0f, 0.1f, 0.3f, 1.0f }
    , m_ShaderLibrary{ Zero::ShaderLibrary::Create() }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
    , m_QuadVertexArray{ Zero::VertexArray::Create() }
{}

ExampleLayer2D::~ExampleLayer2D()
{}

void ExampleLayer2D::OnAttach()
{
    Zero::VertexBufferLayout layout{ { Zero::AttributeType::Float3, "a_Position" } };

    float quadVertices[]{
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.5f,  0.5f,  0.0f, //
        -0.5f, 0.5f,  0.0f, //
    };

    uint32_t quadIndices[]{ 0, 1, 2, 2, 3, 0 };

    m_QuadVertexArray.reset(Zero::VertexArray::Create());

    Zero::Ref<Zero::VertexBuffer> quadVertexBuffer{ Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)) };
    quadVertexBuffer->SetLayout(layout);
    m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

    Zero::Ref<Zero::IndexBuffer> quadIndexBuffer{ Zero::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)) };
    m_QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

    m_ShaderLibrary->Load("D:/Zero/Sandbox/assets/shaders/Flat.glsl");
}

void ExampleLayer2D::OnDetach()
{}

void ExampleLayer2D::OnUpdate(Zero::DeltaTime deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);

    Zero::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Zero::RenderCommand::Clear();

    Zero::Renderer::BeginScene(m_CameraController.GetCamera());

    auto flatShader{ std::dynamic_pointer_cast<Zero::OpenGLShader>(m_ShaderLibrary->Get("Flat")) };
    flatShader->Bind();
    flatShader->SetUniform("u_Color", m_QuadColor);
    Zero::Renderer::Submit(m_QuadVertexArray, flatShader);

    Zero::Renderer::EndScene();
}

void ExampleLayer2D::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
}

void ExampleLayer2D::OnUIRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_QuadColor));
    ImGui::End();
}
