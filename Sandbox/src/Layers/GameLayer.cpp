#include "GameLayer.h"

static constexpr uint32_t s_MapWidth{ 24u };
static constexpr uint32_t s_MapHeight{ 12u };
static const char* s_MapTiles{ "~~~~~~~~~~~~~~~~~~~~~~~~"
                               "~~~~~DDDDDDDDDD~~~~~~~~~"
                               "~~~DDDD~~DDDDDDDDD~~~~~~"
                               "~~~DDDDDDDDDDDDDDDD~~~~~"
                               "~~~DDDDDDDD~~DDDD~~~~~~~"
                               "~~~~DDDDDDD~~DD~~~~~~~~~"
                               "~~~~~DDDDDDDD~~~~~~~~~~~"
                               "~~~~~~~~DDD~~~~~~~~~~~~~"
                               "~~~~~~~~~~~~~DDDD~~~~~~~"
                               "~~~~~~~~~~~~~~DDD~~~~~~~"
                               "~~~~~~~~~~~~~~~~~~~~~~~~"
                               "~~~~~~~~~~~~~~~~~~~~~~~~" };

Zero::Map<char, Zero::Ref<Zero::SubTexture2D>> GameLayer::s_TextureMap{};

GameLayer::GameLayer() : Layer{ "Game" }, m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() } {
}

void GameLayer::OnAttach() {
  m_SpriteSheet = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/RPGpack_sheet_2X.png");

  m_TextureStairs = Zero::SubTexture2D::CreateFromUVs({ .Texture{ m_SpriteSheet }, .Offset{ 0, 11 }, .CellSize{ 128 }, .SpriteSize{ 1, 1 } });
  m_TextureBarrel = Zero::SubTexture2D::CreateFromUVs({ .Texture{ m_SpriteSheet }, .Offset{ 0, 10 }, .CellSize{ 128 }, .SpriteSize{ 1, 1 } });
  m_TextureTree = Zero::SubTexture2D::CreateFromUVs({ .Texture{ m_SpriteSheet }, .Offset{ 2, 1 }, .CellSize{ 128 }, .SpriteSize{ 1, 2 } });

  s_TextureMap['D'] = Zero::SubTexture2D::CreateFromUVs({ .Texture{ m_SpriteSheet }, .Offset{ 6, 11 } });
  s_TextureMap['~'] = Zero::SubTexture2D::CreateFromUVs({ .Texture{ m_SpriteSheet }, .Offset{ 11, 11 } });

  m_CameraController.SetZoomLevel(5.0f);
}

void GameLayer::OnUpdate(const Zero::DeltaTime deltaTime) {
  m_CameraController.OnUpdate(deltaTime);
}

void GameLayer::OnRender() {
  Zero::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
  Zero::RenderCommand::Clear();

  Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

  for (uint32_t y{ 0u }; y < s_MapHeight; ++y) {
    for (uint32_t x{ 0u }; x < s_MapWidth; ++x) {
      const char tile{ s_MapTiles[x + y * s_MapWidth] };
      Zero::Ref<Zero::SubTexture2D> texture{ s_TextureMap.find(tile) != s_TextureMap.end() ? s_TextureMap[tile] : m_TextureTree };
      Zero::Renderer2D::DrawQuad({ .Position{ x - (s_MapWidth / 2.0f), s_MapHeight - y - s_MapHeight / 2.0f }, .SubTexture{ texture } });
    }
  }

  // Zero::Renderer2D::DrawQuad({ .Position{ 0.0f, 0.0f }, .SubTexture{ m_TextureStairs } });
  // Zero::Renderer2D::DrawQuad({ .Position{ 1.0f, 0.0f }, .SubTexture{ m_TextureBarrel } });
  // Zero::Renderer2D::DrawQuad({ .Position{ -1.0f, 0.0f }, .Scale{ 1.0f, 2.0f }, .SubTexture{ m_TextureTree } });

  Zero::Renderer2D::EndScene();
}

void GameLayer::OnUIRender() {
}

void GameLayer::OnEvent(Zero::Event& event) {
  m_CameraController.OnEvent(event);
  Zero::EventDispatcher dispatcher{ event };
  dispatcher.Dispatch<Zero::KeyPressedEvent>(ZR_BIND_FUNCTION(GameLayer::OnKeyPressed));
}

bool GameLayer::OnKeyPressed(Zero::KeyPressedEvent& event) {
  if (event.GetKeyCode() == Zero::KeyCode::ESCAPE) {
    Zero::Application::Get().Close();
    return true;
  }
  return false;
}

void GameLayer::OnDetach() {
}
