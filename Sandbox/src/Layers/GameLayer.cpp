#include "GameLayer.h"

GameLayer::GameLayer()
    : Layer{ "Game" }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
    , m_SpriteSheet{ Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/RPGpack_sheet_2X.png") }
    , m_TextureStairs{ Zero::SubTexture2D::CreateFromUVs(m_SpriteSheet, glm::vec2{ 7.0f, 6.0f }, glm::vec2{ 128.0f }) }
    , m_TextureBarrel{ Zero::SubTexture2D::CreateFromUVs(m_SpriteSheet, glm::vec2{ 8.0f, 2.0f }, glm::vec2{ 128.0f }) }
    , m_TextureTree{ Zero::SubTexture2D::CreateFromUVs(m_SpriteSheet, glm::vec2{ 2.0f, 1.0f }, glm::vec2{ 128.0f }, glm::vec2{ 1.0f, 2.0f }) }
{}

void GameLayer::OnAttach()
{}

void GameLayer::OnDetach()
{}

void GameLayer::OnUpdate(const Zero::DeltaTime deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);
}

void GameLayer::OnRender()
{
    Zero::RenderCommand::Clear();
    Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        Zero::Renderer2D::DrawQuad({ .Position{ 0.0f, 0.0f }, .SubTexture{ m_TextureStairs } });
        Zero::Renderer2D::DrawQuad({ .Position{ 1.0f, 0.0f }, .SubTexture{ m_TextureBarrel } });
        Zero::Renderer2D::DrawQuad({ .Position{ -1.0f, 0.0f }, .Scale{ 1.0f, 2.0f }, .SubTexture{ m_TextureTree } });
    }
    Zero::Renderer2D::EndScene();
}

void GameLayer::OnUIRender()
{}

void GameLayer::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
}
