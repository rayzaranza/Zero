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
        static void Flush();

      public:
        struct QuadProperties
        {
            glm::vec2 Position{ 0.0f };
            float Rotation{ 0.0f };
            glm::vec2 Scale{ 1.0f };
            glm::vec4 Color{ 1.0f };
            glm::vec2 Tiling{ 1.0f };
            Texture2DRef Texture{ nullptr };
        };

        static void DrawQuad(const QuadProperties& quad);
    };
}
