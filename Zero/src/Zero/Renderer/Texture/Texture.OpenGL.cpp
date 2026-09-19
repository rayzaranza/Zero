#define STB_IMAGE_IMPLEMENTATION
#include "Texture.OpenGL.h"
#include "Zero/Core/Core.h"
#include <glad/glad.h>
#include <stb_image.h>

Zero::Texture2DOpenGL::Texture2DOpenGL(const glm::uvec2& size) : m_Size{ size }, m_Format{ GL_RGBA8, GL_RGBA } {
  SetupTextureBuffer();
}

Zero::Texture2DOpenGL::Texture2DOpenGL(const std::string& path) : m_Path{ path } {
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* imageData{ nullptr };
  glm::ivec2 imageSize{};
  int32_t imageChannels{};
  imageData = stbi_load(path.c_str(), &imageSize.x, &imageSize.y, &imageChannels, 0);

  ZR_CORE_ASSERT(imageData, "Failed to load image");
  m_Size = imageSize;
  m_Format = GetTextureFormat(imageChannels);

  SetupTextureBuffer();
  glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, m_Format.image, GL_UNSIGNED_BYTE, imageData);

  stbi_image_free(imageData);
}

Zero::Texture2DOpenGL::~Texture2DOpenGL() {
  glDeleteTextures(1, &m_Id);
}

void Zero::Texture2DOpenGL::Bind(const uint32_t slot) const {
  glBindTextureUnit(slot, m_Id);
}

const glm::uvec2& Zero::Texture2DOpenGL::GetSize() const {
  return m_Size;
}

void Zero::Texture2DOpenGL::SetData(const void* data, const uint32_t size) {
  const uint32_t bytesPerPixel{ m_Format.image == GL_RGBA ? 4u : 3u };
  ZR_CORE_ASSERT(size == m_Size.x * m_Size.y * bytesPerPixel, "Data must be entire texture");
  glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, m_Format.image, GL_UNSIGNED_BYTE, data);
}

uint32_t Zero::Texture2DOpenGL::GetRendererID() const {
  return m_Id;
}

Zero::TextureFormat Zero::Texture2DOpenGL::GetTextureFormat(const int32_t channels) {
  switch (channels) {
    case 4: return { .storage = GL_RGBA8, .image = GL_RGBA };
    case 3: return { .storage = GL_RGB8, .image = GL_RGB };
  }
  ZR_CORE_ASSERT(false, "Texture2D image format not supported");
  return { 0, 0 };
}

void Zero::Texture2DOpenGL::SetupTextureBuffer() {
  glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
  glTextureStorage2D(m_Id, 1, m_Format.storage, m_Size.x, m_Size.y);
  glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
