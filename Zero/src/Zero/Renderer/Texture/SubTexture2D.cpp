#include "SubTexture2D.h"

Zero::SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
  : m_Texture{ texture }
  , m_UVs{ { min.x, min.y }, { max.x, min.y }, { max.x, max.y }, { min.x, max.y } } {
}

const Zero::Ref<Zero::Texture2D> Zero::SubTexture2D::GetTexture() const {
  return m_Texture;
}

const glm::vec2* Zero::SubTexture2D::GetUVs() const {
  return m_UVs;
}

Zero::Ref<Zero::SubTexture2D>
Zero::SubTexture2D::CreateFromUVs(const Ref<Texture2D>& texture, const glm::vec2& position, const glm::vec2& cellSize, const glm::vec2& spriteSize) {
  const glm::vec2& sheetSize{ texture->GetSize() };
  const glm::vec2 min{ (position.x * cellSize.x) / sheetSize.x, (position.y * cellSize.y) / sheetSize.y };
  const glm::vec2 max{ ((position.x + spriteSize.x) * cellSize.x) / sheetSize.x, ((position.y + spriteSize.y) * cellSize.y) / sheetSize.y };
  return CreateRef<SubTexture2D>(texture, min, max);
}
