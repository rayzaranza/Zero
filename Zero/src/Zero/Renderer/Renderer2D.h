#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Renderer/Texture.h"

namespace Zero
{
    class Renderer2D
    {
      public:
        struct QuadProperties
        {
            Vector2 Position{ 0.0f };
            Radians Rotation{ 0.0f };
            Vector2 Scale{ 1.0f };
            Color Color{ Color::White };
            Texture2DRef Texture{ nullptr };
        };

      public:
        static void Initialize();
        static void Destroy();

      public:
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

      public:
        static void DrawQuad(const QuadProperties& quad);
        static void DrawQuad(const Vector2& position, const Radians rotation, const Vector2& scale, const Color& color);
        static void DrawQuad(
            const Vector2& position, const Radians rotation, const Vector2& scale, const Texture2DRef& texture, const Color& tint = Color::White
        );
    };
}
