#include "ExampleLayer2D.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_QuadColor{ 1.0f, 0.1f, 0.3f, 1.0f }
    , m_ShaderLibrary{ Zero::ShaderLibrary::Create() }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
{}

ExampleLayer2D::~ExampleLayer2D()
{}

void ExampleLayer2D::OnAttach()
{
    m_QuadVertexArray = Zero::VertexArray::Create();

    Zero::Ref<Zero::VertexBuffer> quadVertexBuffer{
        Zero::VertexBuffer::Create({ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f })
    };

    Zero::Ref<Zero::IndexBuffer> quadIndexBuffer{ Zero::IndexBuffer::Create({ 0, 1, 2, 2, 3, 0 }) };

    quadVertexBuffer->SetLayout({ { Zero::AttributeType::Float3, "a_Position" } });
    m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);
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

    Zero::Renderer2D::DrawQuad(glm::vec2{ 0.0f }, glm::vec2{ 1.0f }, m_QuadColor);
    Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Zero::Renderer2D::EndScene();
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
