#pragma once

#include "Zero/Camera/Camera.h"

namespace Zero
{
    class Renderer2D
    {
      public:
        static void Initialize();
        static void Destroy();

      public:
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

      public:
        static void DrawQuad(
            const Vector2& position = Vector2{ 0.0f },
            const Vector2& size = Vector2{ 1.0f },
            F32 rotation = 0.0f,
            const Color& color = Color{ 1.0f }
        );

        static void DrawQuad(
            const Vector3& position = Vector3{ 0.0f },
            const Vector2& size = Vector2{ 1.0f },
            F32 rotation = 0.0f,
            const Color& color = Color{ 1.0f }
        );
    };
}
