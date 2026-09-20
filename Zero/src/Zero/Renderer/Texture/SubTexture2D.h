#pragma once
#include "Texture.h"

namespace Zero {
  struct SubTexture2DProps {
    const Ref<Texture2D>& Texture{};
    glm::ivec2 Offset{ 0 };
    glm::uvec2 CellSize{ 128u };
    glm::uvec2 SpriteSize{ 1u };
  };

  class SubTexture2D {
  public:
    SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
    const Ref<Texture2D> GetTexture() const;
    const glm::vec2* GetUVs() const;
    static Ref<SubTexture2D> CreateFromUVs(const SubTexture2DProps& subTexture);

  private:
    Ref<Texture2D> m_Texture;
    glm::vec2 m_UVs[4];
  };
}
