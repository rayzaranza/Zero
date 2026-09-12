#include "ExampleLayer2D.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_QuadColor{ Zero::Color::Blue }
    , m_ShaderLibrary{ Zero::ShaderLibrary::Create() }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
{}

ExampleLayer2D::~ExampleLayer2D()
{}

void ExampleLayer2D::OnAttach()
{
    m_QuadVertexArray = Zero::VertexArray::Create();

    Zero::VertexBufferRef quadVertexBuffer{
        Zero::VertexBuffer::Create({ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f })
    };

    Zero::IndexBufferRef quadIndexBuffer{ Zero::IndexBuffer::Create({ 0, 1, 2, 2, 3, 0 }) };

    quadVertexBuffer->SetLayout({ { Zero::AttributeType::Vector3, "a_Position" } });
    m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);
    m_QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

    m_ShaderLibrary->Load("D:/Zero/Sandbox/assets/shaders/Flat.glsl");
}

void ExampleLayer2D::OnDetach()
{}

void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);
    Zero::RenderCommand::SetClearColor(Zero::Color::Black);
    Zero::RenderCommand::Clear();

    Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Zero::Renderer2D::DrawQuad(Zero::Vector2::Zero, Zero::Vector2::One, 0.0f, m_QuadColor);
    Zero::Renderer2D::DrawQuad(Zero::Vector2{ 0.5f, 1.0f }, Zero::Vector2{ 1.0f, 0.5f }, 0.0f, Zero::Color::Yellow);
    Zero::Renderer2D::EndScene();
}

void ExampleLayer2D::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
}

void ExampleLayer2D::OnUIRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(static_cast<glm::vec4&>(m_QuadColor)));
    ImGui::End();
}
