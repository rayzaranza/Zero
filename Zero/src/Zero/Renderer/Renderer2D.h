#pragma once
#include "Zero/Renderer/Shader/Shader.h"
#include "Zero/Renderer/Buffer/VertexArray.h"
#include "Zero/Renderer/Buffer/VertexBuffer.h"
#include "Zero/Renderer/Texture/Texture.h"
#include "Zero/Renderer/Texture/SubTexture2D.h"
#include "Zero/Camera/Camera.h"
#include "Zero/Camera/EditorCamera.h"


namespace Zero {


static constexpr uint32_t MAX_QUADS{ 20000u };
static constexpr uint32_t QUAD_VERTEX_COUNT{ 4u };
static constexpr uint32_t QUAD_INDEX_COUNT{ 6u };
static constexpr uint32_t MAX_VERTICES{ MAX_QUADS * QUAD_VERTEX_COUNT };
static constexpr uint32_t MAX_INDICES{ MAX_QUADS * QUAD_INDEX_COUNT };
static constexpr uint32_t MAX_TEXTURE_SLOTS{ 32u };
static constexpr uint32_t DEFAULT_TEXTURE_SLOT_INDEX{ 0u };
static constexpr glm::vec2 QUAD_VERTEX_UVS[4]{ { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
static constexpr glm::vec3 QUAD_VERTEX_POSITIONS[4]{
    { -0.5f, -0.5f, 0.0f }, { 0.5f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, { -0.5f, 0.5f, 0.0f }
};


struct QuadProps
{
    glm::mat4 Transform{ 1.0f };
    glm::vec4 Color{ 1.0f };
    Ref<Texture2D> Texture{ nullptr };
    Ref<SubTexture2D> SubTexture{ nullptr };
    glm::vec2 Tiling{ 1.0f };
    int32_t EntityID{ -1 };
};


struct QuadVertex
{
    glm::vec3 Position{ 0.0f };
    glm::vec4 Color{ 1.0f };
    glm::vec2 UV{ 0.0f };
    uint32_t TextureSlot{ 0u };
    glm::vec2 Tiling{ 1.0f };
    int32_t EntityID{ -1 };
};


struct RenderStats
{
    uint32_t DrawCalls{ 0u };
    uint32_t QuadCount{ 0u };

    uint32_t GetTotalVertexCount() const;
    uint32_t GetTotalIndexCount() const;
};


struct Renderer2DData
{
    Ref<VertexArray> QuadVertexArray{};
    Ref<VertexBuffer> QuadVertexBuffer{};
    Ref<Shader> QuadShader{};
    Ref<Texture2D> DefaultTexture{};
    uint32_t QuadIndexCount{ 0u };
    QuadVertex* QuadVertexBufferBase{ nullptr };
    QuadVertex* QuadVertexBufferPointer{ nullptr };
    FixedArray<Ref<Texture2D>, MAX_TEXTURE_SLOTS> Textures{};
    uint32_t TextureSlotIndex{ 1u };
    RenderStats Stats{};
};


class Renderer2D
{
  public:
    static void Initialize();
    static void Destroy();
    static void BeginScene(const Camera& camera, const glm::mat4& transform = glm::mat4{ 1.0f });
    static void BeginScene(const EditorCamera& camera);
    static void BeginScene(const CameraOrthographic& camera);
    static void EndScene();
    static void Flush();
    static void DrawQuad(const QuadProps& quad);
    static void ResetStats();
    static const RenderStats& GetStats();

  private:
    static void FlushAndReset();
    static void StartBatch();
    static void SetQuadMatrices(const glm::mat4& projection);
};


}
