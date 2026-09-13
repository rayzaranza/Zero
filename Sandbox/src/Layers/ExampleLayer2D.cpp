#include "ExampleLayer2D.h"

#include <imgui.h>

#include <chrono>
#include <glm/gtc/type_ptr.hpp>
#include <print>

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
    , m_Texture{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg") }
{}

ExampleLayer2D::~ExampleLayer2D()
{}

void ExampleLayer2D::OnAttach()
{
    ZR_PROFILE_FUNCTION();
}

void ExampleLayer2D::OnDetach()
{
    ZR_PROFILE_FUNCTION();
}

void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    ZR_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(deltaTime);
}

void ExampleLayer2D::OnRender()
{
    ZR_PROFILE_FUNCTION();

    {
        ZR_PROFILE_SCOPE("Renderer Prep");

        Zero::RenderCommand::Clear(Zero::Color::Black);
    }

    {
        ZR_PROFILE_SCOPE("Renderer Draw Scene");

        Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Zero::Renderer2D::DrawQuad(m_QuadProperties);
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

    ImGui::Begin("Quad Properties");
    ImGui::DragFloat2("Position", ValuePointer(m_QuadProperties.Position), 0.001f);
    ImGui::DragFloat2("Scale", ValuePointer(m_QuadProperties.Scale), 0.001f);
    ImGui::SliderAngle("Rotation", ValuePointer(m_QuadProperties.Rotation));
    ImGui::ColorEdit4("Color", ValuePointer(m_QuadProperties.Color));
    ImGui::End();
}
