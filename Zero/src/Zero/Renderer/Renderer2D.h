#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Core/Core.h"

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
            const Vector2& position = Vector2::Zero,
            const Vector2& size = Vector2::One,
            const Degrees rotation = 0.0f,
            const Color& color = Color::White
        );

        static void DrawQuad(
            const Vector3& position = Vector3::Zero,
            const Vector2& size = Vector2::One,
            const Degrees rotation = 0.0f,
            const Color& color = Color::White
        );
    };
}
