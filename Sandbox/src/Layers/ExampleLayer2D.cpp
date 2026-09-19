#include "ExampleLayer2D.h"

#include <imgui.h>

//======================================================================================
//  Creation
//======================================================================================

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
    , m_Texture{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg") }
    , m_TextureB{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png") }
    , m_Quads{
        {.Position{ -0.5f, 0.0f }, .Rotation{ glm::radians(45.0f) }, .Scale{ 0.5f }, .Color{ 0.8f, 0.2f, 0.3f, 1.0f } },
        {.Position{ -1.1f, -0.5f }, .Scale{ 0.2f } },
        {.Position{ 0.5f, -0.2f }, .Scale{ 1.0f }, .Color{ 0.1f, 0.4f, 0.1f, 1.0f } },
        {.Position{ 0.5f, -0.5f }, .Scale{ 0.5f, 0.75f }, .Texture{ m_Texture } },
    },
    m_Particle{
        .Position{ 0.0f, 0.0f },
        .Velocity{ 0.0f, 0.0f },
        .VelocityVariation{ 3.0f, 1.0f },
        .ColorBegin{ 254 / 255.0f, 212 / 255.0f, 124 / 255.0f, 1.0f },
        .ColorEnd{ 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f },
        .SizeBegin{ 0.5f },
        .SizeEnd{ 0.0f },
        .SizeVariation{ 0.3f },
        .LifeTime{ 5.0f },
    }
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

    m_Quads[1].Rotation += deltaTime * 2.0f;

    m_CameraController.OnUpdate(deltaTime);

    if (Zero::Input::IsMouseButtonPressed(Zero::MouseButton::LEFT))
    {
        const glm::vec2& mouse{ Zero::Input::GetMousePosition() };
        const glm::uvec2& size{ Zero::Application::Get().GetWindow().GetSize() };

        auto bounds{ m_CameraController.GetBounds() };

        const glm::vec2& pos{ m_CameraController.GetCamera().GetPosition() };
        const float x{ (mouse.x / size.x) * bounds.GetWidth() - bounds.GetWidth() * 0.5f };
        const float y{ bounds.GetHeight() * 0.5f - (mouse.y / size.y) * bounds.GetHeight() };
        m_Particle.Position = { x + pos.x, y + pos.y };

        for (int32_t i{ 0 }; i < 50; i++)
        {
            m_ParticleSystem.Emit(m_Particle);
        }
    }

    m_ParticleSystem.OnUpdate(deltaTime);
}

//======================================================================================
//  Render
//======================================================================================
void ExampleLayer2D::OnRender()
{
    Zero::Renderer2D::ResetStats();

    ZR_PROFILE_FUNCTION();
    {
        ZR_PROFILE_SCOPE("Renderer Setup");

        Zero::RenderCommand::Clear({ 0.02f, 0.02f, 0.022f, 1.0f });
    }
    {
        ZR_PROFILE_SCOPE("Renderer Draw");

        Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y{ -5.0f }; y < 5.0f; y += 0.1f)
        {
            for (float x{ -5.0f }; x < 5.0f; x += 0.1f)
            {
                Zero::Renderer2D::DrawQuad(
                    { .Position{ x, y }, .Scale{ 0.09f }, .Color{ (x + 5.0f) / 10.0f, 0.0f, (y + 5.0f) / 10.0f, 1.0f } }
                );
            }
        }

        for (const auto& quad : m_Quads)
        {
            Zero::Renderer2D::DrawQuad(quad);
        }

        Zero::Renderer2D::EndScene();

        m_ParticleSystem.OnRender(m_CameraController.GetCamera());
    }
}

//======================================================================================
//  UI
//======================================================================================
void ExampleLayer2D::OnUIRender()
{
    ZR_PROFILE_FUNCTION();

    const Zero::RenderStats& stats{ Zero::Renderer2D::GetStats() };

    ImGui::Begin("Settings");
    ImGui::Text("Renderer2D Stats");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::End();
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
