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
    m_Texture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
}

void ExampleLayer2D::OnDetach()
{}

void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);
}

void ExampleLayer2D::OnRender()
{
    Zero::RenderCommand::Clear(Zero::Color::Black);

    Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Zero::Renderer2D::DrawQuad({ -1.0f, -0.5f }, 0.0f, Zero::Vector2{ 10.0f }, m_Texture);
    Zero::Renderer2D::DrawQuad(Zero::Vector2::Zero, 0.0f, Zero::Vector2::One, Zero::Color::Red);
    Zero::Renderer2D::DrawQuad({ 0.5f, 1.0f }, 0.0f, Zero::Vector2::One, Zero::Color::Yellow);
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
