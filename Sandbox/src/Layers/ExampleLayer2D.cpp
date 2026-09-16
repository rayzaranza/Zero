#include "ExampleLayer2D.h"

#include <imgui.h>

#include <chrono>
#include <glm/gtc/type_ptr.hpp>
#include <print>

//======================================================================================
//  Creation
//======================================================================================

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
    , m_Texture{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg") }
    , m_TextureB{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png") }
{}

//======================================================================================
//  Setup
//======================================================================================
void ExampleLayer2D::OnAttach()
{
    ZR_PROFILE_FUNCTION();
}

//======================================================================================
//  Update
//======================================================================================
void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    ZR_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(deltaTime);
}

//======================================================================================
//  Render
//======================================================================================
void ExampleLayer2D::OnRender()
{
    ZR_PROFILE_FUNCTION();
    {
        ZR_PROFILE_SCOPE("Renderer Setup");

        Zero::RenderCommand::Clear({ 0.02f, 0.02f, 0.022f, 1.0f });
    }
    {
        ZR_PROFILE_SCOPE("Renderer Draw");

        Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Zero::Renderer2D::DrawQuad({ .Position{ -0.5f, 0.0f }, .Scale{ 0.5f }, .Color{ 0.8f, 0.2f, 0.3f, 1.0f } });
        Zero::Renderer2D::DrawQuad({ .Position{ 0.5f, -0.5f }, .Scale{ 0.5f, 0.75f }, .Color{ 0.2f, 0.3f, 0.8f, 1.0f } });
        Zero::Renderer2D::DrawQuad({ .Position{ 0.5f, -0.2f }, .Scale{ 1.0f }, .Texture{ m_Texture } });
        Zero::Renderer2D::DrawQuad({ .Position{ -1.1f, -0.5f }, .Scale{ 0.2f }, .Texture{ m_TextureB } });

        Zero::Renderer2D::EndScene();
    }
}

//======================================================================================
//  UI
//======================================================================================
void ExampleLayer2D::OnUIRender()
{
    ZR_PROFILE_FUNCTION();
}

//======================================================================================
//  Events
//======================================================================================
void ExampleLayer2D::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
    Zero::EventDispatcher dispatcher{ event };
    dispatcher.Dispatch<Zero::KeyPressedEvent>(ZR_BIND_FUNCTION(ExampleLayer2D::OnKeyPressed));
}

bool ExampleLayer2D::OnKeyPressed(Zero::KeyPressedEvent& event)
{
    if (event.GetKeyCode() == Zero::KeyCode::ESCAPE)
    {
        Zero::Application::Get().Close();
        ZR_LOG("Close app");
    }

    return false;
}

//======================================================================================
//  Destroy
//======================================================================================
void ExampleLayer2D::OnDetach()
{
    ZR_PROFILE_FUNCTION();
}

ExampleLayer2D::~ExampleLayer2D()
{}
