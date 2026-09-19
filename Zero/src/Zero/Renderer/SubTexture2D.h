#pragma once

#include "Zero/Renderer/Texture.h"

namespace Zero
{
    class SubTexture2D
    {
      public:
        SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

      public:
        const Ref<Texture2D> GetTexture() const { return m_Texture; }
        const glm::vec2* GetUVs() const { return m_UVs; }

        static Ref<SubTexture2D> CreateFromUVs(
            const Ref<Texture2D>& texture, const glm::vec2& position, const glm::vec2& cellSize, const glm::vec2& spriteSize = glm::vec2{ 1.0f }
        );

      private:
        Ref<Texture2D> m_Texture;
        glm::vec2 m_UVs[4];
    };
}
