#include "Zero/Renderer/OpenGL/OpenGLTexture.h"

#include "Zero/Core/Core.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

namespace Zero
{
    static OpenGLTexture2D::Format GetTextureFormat(const I32 channels);

    OpenGLTexture2D::OpenGLTexture2D(const glm::uvec2& size) : m_Size{ size }, m_Format{ GL_RGBA8, GL_RGBA }
    {
        ZR_PROFILE_FUNCTION();

        SetupTextureBuffer();
    }

    OpenGLTexture2D::OpenGLTexture2D(const String& path) : m_Path{ path }
    {
        ZR_PROFILE_FUNCTION();

        stbi_set_flip_vertically_on_load(1);

        stbi_uc* imageData{ nullptr };
        glm::ivec2 imageSize{};
        I32 imageChannels{};
        {
            ZR_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const String& path)");

            imageData = stbi_load(path.c_str(), &imageSize.x, &imageSize.y, &imageChannels, 0);
        }

        ZR_CORE_ASSERT(imageData, "Failed to load image");
        m_Size = imageSize;
        m_Format = GetTextureFormat(imageChannels);

        SetupTextureBuffer();
        glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, m_Format.image, GL_UNSIGNED_BYTE, imageData);

        stbi_image_free(imageData);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        ZR_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_Id);
    }

    void OpenGLTexture2D::Bind(const U32 slot) const
    {
        ZR_PROFILE_FUNCTION();

        glBindTextureUnit(0, m_Id);
    }

    void OpenGLTexture2D::SetData(const void* data, const U32 size)
    {
        ZR_PROFILE_FUNCTION();

        const U32 bytesPerPixel{ m_Format.image == GL_RGBA ? 4u : 3u };
        ZR_CORE_ASSERT(size == m_Size.x * m_Size.y * bytesPerPixel, "Data must be entire texture");
        glTextureSubImage2D(m_Id, 0, 0, 0, m_Size.x, m_Size.y, m_Format.image, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::SetupTextureBuffer()
    {
        ZR_PROFILE_FUNCTION();

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
