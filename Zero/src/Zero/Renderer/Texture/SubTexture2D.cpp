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

Zero::Ref<Zero::SubTexture2D> Zero::SubTexture2D::CreateFromUVs(const SubTexture2DProps& subTexture) {
  const glm::vec2& sheet{ subTexture.Texture->GetSize() };
  const glm::vec2& pos{ static_cast<glm::vec2>(subTexture.Offset) };
  const glm::vec2& cell{ static_cast<glm::vec2>(subTexture.CellSize) };
  const glm::vec2& sprite{ static_cast<glm::vec2>(subTexture.SpriteSize) };

  const glm::vec2 min{ (pos.x * cell.x) / sheet.x, (pos.y * cell.y) / sheet.y };
  const glm::vec2 max{ ((pos.x + sprite.x) * cell.x) / sheet.x, ((pos.y + sprite.y) * cell.y) / sheet.y };

  return CreateRef<SubTexture2D>(subTexture.Texture, min, max);
}
