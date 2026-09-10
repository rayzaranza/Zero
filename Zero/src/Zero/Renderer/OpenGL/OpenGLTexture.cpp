#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

namespace Zero
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path{ path }
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* image{ stbi_load(path.c_str(), &width, &height, &channels, 0) };
        ZERO_CORE_ASSERT(image, "Failed to load image");

        m_Width = width;
        m_Height = height;

        GLenum internalFormat{};
        GLenum dataFormat{};

        switch (channels)
        {
            case 4:
            {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
                break;
            }
            case 3:
            {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                break;
            }
            default: ZERO_CORE_ASSERT(false, "Texture2D image format not supported"); break;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
        glTextureStorage2D(m_Id, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_Id, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Id);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(0, m_Id);
    }
}
