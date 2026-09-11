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
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    };
}
