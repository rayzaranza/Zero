#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Renderer/Texture.h"

namespace Zero
{
    //======================================================================================
    //  Constants
    //======================================================================================
    static constexpr uint32_t MAX_QUADS{ 20000u };
    static constexpr uint32_t QUAD_VERTEX_COUNT{ 4u };
    static constexpr uint32_t QUAD_INDEX_COUNT{ 6u };
    static constexpr uint32_t MAX_VERTICES{ MAX_QUADS * QUAD_VERTEX_COUNT };
    static constexpr uint32_t MAX_INDICES{ MAX_QUADS * QUAD_INDEX_COUNT };
    static constexpr uint32_t MAX_TEXTURE_SLOTS{ 32u };
    static constexpr uint32_t DEFAULT_TEXTURE_SLOT_INDEX{ 0u };
    static constexpr glm::vec2 QUAD_VERTEX_POSITIONS[4]{ { -0.5f, -0.5f }, { 0.5f, -0.5f }, { 0.5f, 0.5f }, { -0.5f, 0.5f } };
    static constexpr glm::vec2 QUAD_VERTEX_UVS[4]{ { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    //======================================================================================
    //  QuadProperties
    //======================================================================================
    struct QuadProperties
    {
        glm::vec2 Position{ 0.0f };
        float Rotation{ 0.0f };
        glm::vec2 Scale{ 1.0f };
        glm::vec4 Color{ 1.0f };
        Ref<Texture2D> Texture{ nullptr };
        glm::vec2 Tiling{ 1.0f };
    };

    //======================================================================================
    //  Render Statistics
    //======================================================================================
    struct RenderStats
    {
        uint32_t DrawCalls{ 0u };
        uint32_t QuadCount{ 0u };

        uint32_t GetTotalVertexCount() const { return QuadCount * QUAD_VERTEX_COUNT; }
        uint32_t GetTotalIndexCount() const { return QuadCount * QUAD_INDEX_COUNT; }
    };

    //======================================================================================
    //  Renderer2D
    //======================================================================================
    class Renderer2D
    {
      public:
        static void Initialize();
        static void Destroy();
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();
        static void DrawQuad(const QuadProperties& quad);
        static void ResetStats();
        static const RenderStats& GetStats();

      private:
        static void FlushAndReset();
    };
}
