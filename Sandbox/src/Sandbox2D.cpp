#include "Sandbox2D.h"
#include <imgui.h>


Sandbox2D::Sandbox2D() : Zero::Layer{ "Sandbox2D" }, m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
{
}


Sandbox2D::~Sandbox2D()
{
}


void Sandbox2D::OnAttach()
{
    m_Texture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/test.jpg");
    m_TextureCheckerboard = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
}


void Sandbox2D::OnDetach()
{
}


void Sandbox2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);
}


void Sandbox2D::OnRender()
{
    Zero::Renderer2D::ResetStats();
    Zero::RenderCommand::Clear({ 0.02f, 0.02f, 0.022f, 1.0f });
    Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Zero::Renderer2D::EndScene();
}


void Sandbox2D::OnUIRender()
{
    const Zero::RenderStats& stats{ Zero::Renderer2D::GetStats() };

    ImGui::Begin("Settings");
    ImGui::Text("Renderer2D Stats");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::End();
}


void Sandbox2D::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
    Zero::EventDispatcher dispatcher{ event };
    dispatcher.Dispatch<Zero::KeyPressedEvent>(ZR_BIND_FUNCTION(Sandbox2D::OnKeyPressed));
}


bool Sandbox2D::OnKeyPressed(Zero::KeyPressedEvent& event)
{
    if (event.GetKeyCode() == Zero::KeyCode::ESCAPE)
    {
        Zero::Application::Get().Close();
        return true;
    }

    return false;
}
