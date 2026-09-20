#pragma once
#include "Buffer/VertexArray.h"
#include "RendererAPI.h"

namespace Zero {
  class RenderCommand {
  public:
    static void Initialize();
    static void Clear();
    static void SetClearColor(const glm::vec4& color);
    static void Clear(const glm::vec4& color);
    static void SetViewport(const glm::ivec2& position, const glm::uvec2& size);
    static void DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount = 0);

  private:
    static Scope<RendererAPI> s_RendererAPI;
  };
}
