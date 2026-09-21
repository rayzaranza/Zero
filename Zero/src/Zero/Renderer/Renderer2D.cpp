#include "Renderer2D.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/VertexBuffer.h"
#include "RenderCommand.h"
#include "Shader/Shader.h"
#include "Zero/Math/Math.h"
#include <glm/gtc/matrix_transform.hpp>

struct Renderer2DData {
  Zero::Ref<Zero::VertexArray> QuadVertexArray{};
  Zero::Ref<Zero::VertexBuffer> QuadVertexBuffer{};
  Zero::Ref<Zero::Shader> QuadShader{};
  Zero::Ref<Zero::Texture2D> DefaultTexture{};
  uint32_t QuadIndexCount{ 0u };
  Zero::QuadVertex* QuadVertexBufferBase{ nullptr };
  Zero::QuadVertex* QuadVertexBufferPointer{ nullptr };
  Zero::FixedArray<Zero::Ref<Zero::Texture2D>, Zero::MAX_TEXTURE_SLOTS> Textures{};
  uint32_t TextureSlotIndex{ 1u };
  Zero::RenderStats Stats{};
};

static Renderer2DData s_Data{};

void Zero::Renderer2D::Initialize() {
  s_Data.QuadVertexArray = VertexArray::Create();
  s_Data.QuadVertexBuffer = VertexBuffer::Create(MAX_VERTICES * sizeof(QuadVertex));
  s_Data.QuadVertexBuffer->SetLayout(
    { { VertexAttributeType::Vector2, "a_Position" },
      { VertexAttributeType::Vector4, "a_Color" },
      { VertexAttributeType::Vector2, "a_UV" },
      { VertexAttributeType::Float, "a_TextureSlot" },
      { VertexAttributeType::Vector2, "a_Tiling" } }
  );
  s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

  s_Data.QuadVertexBufferBase = new QuadVertex[MAX_VERTICES];
  uint32_t* quadIndices{ new uint32_t[MAX_INDICES] };
  uint32_t offset{ 0u };
  for (uint32_t i{ 0u }; i < MAX_INDICES; i += QUAD_INDEX_COUNT) {
    quadIndices[i + 0u] = offset + 0u;
    quadIndices[i + 1u] = offset + 1u;
    quadIndices[i + 2u] = offset + 2u;
    quadIndices[i + 3u] = offset + 2u;
    quadIndices[i + 4u] = offset + 3u;
    quadIndices[i + 5u] = offset + 0u;
    offset += QUAD_VERTEX_COUNT;
  }

  Ref<IndexBuffer> quadIndexBuffer{ IndexBuffer::Create(quadIndices, MAX_INDICES) };
  s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
  delete[] quadIndices;

  s_Data.DefaultTexture = Texture2D::Create(glm::uvec2{ 1u });
  constexpr uint32_t defaultTextureData{ 0xffffffff };
  s_Data.DefaultTexture->SetData(&defaultTextureData, sizeof(uint32_t));
  s_Data.Textures[DEFAULT_TEXTURE_SLOT_INDEX] = s_Data.DefaultTexture;

  int32_t textureSamplers[MAX_TEXTURE_SLOTS]{};
  for (uint32_t i{ 0u }; i < MAX_TEXTURE_SLOTS; ++i) {
    textureSamplers[i] = i;
  }

  s_Data.QuadShader = Shader::Create("D:/Zero/Sandbox/assets/shaders/Default.glsl");
  s_Data.QuadShader->Bind();
  s_Data.QuadShader->SetIntArray("u_Textures", textureSamplers, MAX_TEXTURE_SLOTS);
}

void Zero::Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform) {
  s_Data.QuadShader->Bind();
  s_Data.QuadShader->SetMatrix4("u_ViewProjectionMatrix", camera.GetProjection() * glm::inverse(transform));
  s_Data.QuadShader->SetMatrix4("u_ModelMatrix", { 1.0f });
  s_Data.QuadIndexCount = 0u;
  s_Data.QuadVertexBufferPointer = s_Data.QuadVertexBufferBase;
  s_Data.TextureSlotIndex = 1u;
}

void Zero::Renderer2D::BeginScene(const CameraOrthographic& camera) {
  s_Data.QuadShader->Bind();
  s_Data.QuadShader->SetMatrix4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
  s_Data.QuadShader->SetMatrix4("u_ModelMatrix", { 1.0f });
  s_Data.QuadIndexCount = 0u;
  s_Data.QuadVertexBufferPointer = s_Data.QuadVertexBufferBase;
  s_Data.TextureSlotIndex = 1u;
}

static glm::vec2 GetTansformedVertexPosition(const uint32_t index, const glm::mat4& transform) {
  const glm::vec4 position{ Zero::QUAD_VERTEX_POSITIONS[index], 0.0f, 1.0f };
  const glm::vec4 result{ transform * position };
  return { result.x, result.y };
}

void Zero::Renderer2D::DrawQuad(const QuadProps& quad) {
  if (s_Data.QuadIndexCount >= MAX_INDICES) {
    FlushAndReset();
  }

  float textureIndex{ 0.0f };
  const Ref<Texture2D> texture{ quad.SubTexture ? quad.SubTexture->GetTexture() : quad.Texture };
  if (texture) {
    for (uint32_t i{ 1u }; i < s_Data.TextureSlotIndex; i++) {
      if (s_Data.Textures[i]->GetRendererID() == texture->GetRendererID()) {
        textureIndex = static_cast<float>(i);
        break;
      }
    }
    if (textureIndex == 0.0f) {
      textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
      s_Data.Textures[s_Data.TextureSlotIndex] = texture;
      s_Data.TextureSlotIndex++;
    }
  }

  const glm::vec2* uvs{ quad.SubTexture ? quad.SubTexture->GetUVs() : QUAD_VERTEX_UVS };

  for (uint32_t i{ 0u }; i < 4u; ++i) {
    *s_Data.QuadVertexBufferPointer = QuadVertex{
      .Position{ GetTansformedVertexPosition(i, quad.Transform) },
      .Color{ quad.Color },
      .UV{ uvs[i] },
      .TextureSlot{ textureIndex },
      .Tiling{ quad.Tiling },
    };
    s_Data.QuadVertexBufferPointer++;
  }

  s_Data.QuadIndexCount += QUAD_INDEX_COUNT;
  s_Data.Stats.QuadCount++;
}

void Zero::Renderer2D::Flush() {
  for (uint32_t i{ 0u }; i < s_Data.TextureSlotIndex; i++) {
    s_Data.Textures[i]->Bind(i);
  }
  RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
  s_Data.Stats.DrawCalls++;
}

void Zero::Renderer2D::EndScene() {
  uint32_t dataSize{ static_cast<uint32_t>((uint8_t*)s_Data.QuadVertexBufferPointer - (uint8_t*)s_Data.QuadVertexBufferBase) };
  s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
  Flush();
}

void Zero::Renderer2D::Destroy() {
}

void Zero::Renderer2D::FlushAndReset() {
  EndScene();
  s_Data.QuadIndexCount = 0u;
  s_Data.QuadVertexBufferPointer = s_Data.QuadVertexBufferBase;
  s_Data.TextureSlotIndex = 1u;
}

void Zero::Renderer2D::ResetStats() {
  memset(&s_Data.Stats, 0u, sizeof(RenderStats));
}

const Zero::RenderStats& Zero::Renderer2D::GetStats() {
  return s_Data.Stats;
}

uint32_t Zero::RenderStats::GetTotalVertexCount() const {
  return QuadCount * QUAD_VERTEX_COUNT;
}

uint32_t Zero::RenderStats::GetTotalIndexCount() const {
  return QuadCount * QUAD_INDEX_COUNT;
}
