#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

#include <tuple>

namespace Zero
{
    static struct TextureFormat
    {
        U32 internal{};
        U32 data{};
    };

    TextureFormat GetTextureFormat(const I32 channels);

    OpenGLTexture2D::OpenGLTexture2D(const String& path) : m_Path{ path }
    {
        stbi_set_flip_vertically_on_load(1);
        Vector2i size{};
        I32 channels;
        stbi_uc* image{ stbi_load(path.c_str(), &size.x, &size.y, &channels, 0) };
        ZR_CORE_ASSERT(image, "Failed to load image");
        m_Size = size;

        const TextureFormat format{ GetTextureFormat(channels) };
        glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
        glTextureStorage2D(m_Id, 1, format.internal, m_Size.x, m_Size.y);
        glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, format.data, GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Id);
    }

    void OpenGLTexture2D::Bind(const U32 slot) const
    {
        glBindTextureUnit(0, m_Id);
    }

    TextureFormat GetTextureFormat(const I32 channels)
    {
        switch (channels)
        {
            case 4: return TextureFormat{ GL_RGBA8, GL_RGBA };
            case 3: return TextureFormat{ GL_RGB8, GL_RGB };
            default:
            {
                ZR_CORE_ASSERT(false, "Texture2D image format not supported");
                return TextureFormat{ 0, 0 };
            }
        }
    }
}
