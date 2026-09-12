#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Renderer/Texture.h"

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
        static void DrawQuad(const Vector2& position, const Degrees rotation, const Vector2& scale, const Color& color);
        static void DrawQuad(const Vector2& position, const Degrees rotation, const Vector2& scale, const Texture2DRef& texture);
    };
}
