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
            glm::vec2 Position{ 0.0f };
            Radians Rotation{ 0.0f };
            glm::vec2 Scale{ 1.0f };
            glm::vec4 Color{ 1.0f };
            glm::vec2 Tiling{ 1.0f };
            Texture2DRef Texture{ nullptr };
        };

      public:
        static void Initialize();
        static void Destroy();

      public:
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

      public:
        static void DrawQuad(const QuadProperties& quad);
        static void DrawQuad(const glm::vec2& position, const Radians rotation, const glm::vec2& scale, const glm::vec4& color);
        static void DrawQuad(
            const glm::vec2& position,
            const Radians rotation,
            const glm::vec2& scale,
            const Texture2DRef& texture,
            const glm::vec4& tint = glm::vec4{ 1.0f },
            const glm::vec2& tiling = glm::vec2{ 1.0f }
        );
    };
}
