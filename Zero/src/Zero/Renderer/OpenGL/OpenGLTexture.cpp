#include "Zero/Renderer/OpenGL/OpenGLTexture.h"

#include "Zero/Core/Core.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

namespace Zero
{
    static OpenGLTexture2D::Format GetTextureFormat(const I32 channels);

    OpenGLTexture2D::OpenGLTexture2D(const Vector2u& size) : m_Size{ size }, m_Format{ GL_RGBA8, GL_RGBA }
    {
        SetupTextureBuffer();
    }

    OpenGLTexture2D::OpenGLTexture2D(const String& path) : m_Path{ path }
    {
        stbi_set_flip_vertically_on_load(1);
        Vector2i size{};
        I32 channels;
        stbi_uc* image{ stbi_load(path.c_str(), &size.x, &size.y, &channels, 0) };
        ZR_CORE_ASSERT(image, "Failed to load image");
        m_Size = size;
        m_Format = GetTextureFormat(channels);

        SetupTextureBuffer();
        glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, m_Format.image, GL_UNSIGNED_BYTE, image);

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

    void OpenGLTexture2D::SetData(const void* data, const U32 size)
    {
        const U32 bytesPerPixel{ m_Format.image == GL_RGBA ? 4u : 3u };
        ZR_CORE_ASSERT(size == m_Size.x * m_Size.y * bytesPerPixel, "Data must be entire texture");
        glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, m_Format.image, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::SetupTextureBuffer()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
        glTextureStorage2D(m_Id, 1, m_Format.storage, m_Size.x, m_Size.y);

        glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::Format GetTextureFormat(const I32 channels)
    {
        switch (channels)
        {
            case 4: return { .storage = GL_RGBA8, .image = GL_RGBA };
            case 3: return { .storage = GL_RGB8, .image = GL_RGB };
        }

        ZR_CORE_ASSERT(false, "Texture2D image format not supported");
        return { 0, 0 };
    }
}
