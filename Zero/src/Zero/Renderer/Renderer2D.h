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
            const glm::vec2& position = glm::vec2{ 0.0f },
            const glm::vec2& size = glm::vec2{ 1.0f },
            float rotation = 0.0f,
            const glm::vec4& color = glm::vec4{ 1.0f }
        );

        static void DrawQuad(
            const glm::vec3& position = glm::vec3{ 0.0f },
            const glm::vec2& size = glm::vec2{ 1.0f },
            float rotation = 0.0f,
            const glm::vec4& color = glm::vec4{ 1.0f }
        );
    };
}
