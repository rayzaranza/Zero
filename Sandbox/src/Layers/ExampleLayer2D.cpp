#include "ExampleLayer2D.h"

#include <imgui.h>

#include <chrono>
#include <glm/gtc/type_ptr.hpp>
#include <print>

constexpr Zero::I32 QUADS_COUNT{ 6 };

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

    m_QuadsProperties.reserve(QUADS_COUNT);

    for (Zero::I32 index{ 0 }; index < QUADS_COUNT; ++index)
    {
        const Zero::F32 i{ static_cast<Zero::F32>(index) };

        const Zero::Renderer2D::QuadProperties quad{
            .Position{ i * 1.12f, 0.0f },
            .Rotation{ i * 360.0f },
            .Color{ 1.0f - i * 0.123f, i * 0.33f, i * 0.1f, 1.0f },
        };

        m_QuadsProperties.push_back(quad);
    }
}

void ExampleLayer2D::OnDetach()
{
    ZR_PROFILE_FUNCTION();
}

void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    ZR_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(deltaTime);

    for (Zero::Renderer2D::QuadProperties& quadProperties : m_QuadsProperties)
    {
        quadProperties.Rotation += deltaTime;
    }
}

void ExampleLayer2D::OnRender()
{
    ZR_PROFILE_FUNCTION();

    {
        ZR_PROFILE_SCOPE("Renderer Prep");

        Zero::RenderCommand::Clear(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
    }

    {
        ZR_PROFILE_SCOPE("Renderer Draw Scene");

        Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

        for (const Zero::Renderer2D::QuadProperties& quadProperties : m_QuadsProperties)
        {
            Zero::Renderer2D::DrawQuad(quadProperties);
        }
    }

    Zero::Renderer2D::EndScene();
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

    // ImGui::Begin("Quad Properties");
    //  ImGui::DragFloat2("Position", glm::value_ptr(m_QuadProperties.Position), 0.001f);
    //  ImGui::DragFloat2("Scale", glm::value_ptr(m_QuadProperties.Scale), 0.001f);
    //  ImGui::SliderAngle("Rotation", &m_QuadProperties.Rotation);
    //  ImGui::ColorEdit4("Color", glm::value_ptr(m_QuadProperties.Color));
    //  ImGui::DragFloat2("Texture Tiling", glm::value_ptr(m_QuadProperties.Tiling));
    // ImGui::End();
}
