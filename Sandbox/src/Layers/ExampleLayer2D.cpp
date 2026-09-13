#include "ExampleLayer2D.h"

#include <imgui.h>

#include <chrono>
#include <glm/gtc/type_ptr.hpp>
#include <print>

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_QuadColor{ Zero::Color::Blue }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
{}

ExampleLayer2D::~ExampleLayer2D()
{}

void ExampleLayer2D::OnAttach()
{
    ZR_PROFILE_FUNCTION();

    m_Texture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
}

void ExampleLayer2D::OnDetach()
{}

void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    ZR_PROFILE_FUNCTION();

    {
        ZR_PROFILE_SCOPE("Camera Controller Update");
        m_CameraController.OnUpdate(deltaTime);
    }
}

void ExampleLayer2D::OnRender()
{
    ZR_PROFILE_FUNCTION();

    {
        ZR_PROFILE_SCOPE("Renderer Setup");
        Zero::RenderCommand::Clear(Zero::Color::Black);
    }

    {
        ZR_PROFILE_SCOPE("Renderer Draw");
        Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Zero::Renderer2D::DrawQuad({ -1.0f, -0.5f }, 0.0f, Zero::Vector2{ 10.0f }, m_Texture);
        Zero::Renderer2D::DrawQuad(Zero::Vector2::Zero, 0.0f, Zero::Vector2::One, Zero::Color::Red);
        Zero::Renderer2D::DrawQuad({ 0.5f, 1.0f }, 0.0f, Zero::Vector2::One, m_QuadColor);
        Zero::Renderer2D::EndScene();
    }
}

void ExampleLayer2D::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
    Zero::EventDispatcher dispatcher{ event };
    dispatcher.Dispatch<Zero::KeyPressedEvent>(ZR_BIND_FUNCTION(ExampleLayer2D::OnKeyPressed));
}

Zero::Boolean ExampleLayer2D::OnKeyPressed(Zero::KeyPressedEvent& event)
{
    if (event.GetKeyCode() == Zero::KeyCode::ESCAPE)
    {
        Zero::Application::Get().Close();
        ZR_LOG("Close app");
    }

    return false;
}

void ExampleLayer2D::OnUIRender()
{
    ZR_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(static_cast<glm::vec4&>(m_QuadColor)));
    ImGui::End();
}
