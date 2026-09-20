#pragma once
#include "Texture.h"

namespace Zero {
  struct TextureFormat {
    uint32_t storage{};
    uint32_t image{};
  };

  class Texture2DOpenGL : public Texture2D {
  public:
    Texture2DOpenGL(const glm::uvec2& size);
    Texture2DOpenGL(const std::string& path);
    virtual ~Texture2DOpenGL();
    virtual void Bind(const uint32_t slot = 0) const override;
    virtual const glm::uvec2& GetSize() const override;
    virtual void SetData(const void* data, const uint32_t size) override;
    virtual uint32_t GetRendererID() const override;

  private:
    TextureFormat GetTextureFormat(const int32_t channels);
    void SetupTextureBuffer();
    uint32_t m_Id{};
    std::string m_Path{};
    glm::uvec2 m_Size{};
    TextureFormat m_Format{};
  };
}
