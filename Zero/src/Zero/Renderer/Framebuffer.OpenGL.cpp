#include "Zero/Renderer/Framebuffer.OpenGL.h"

#include <glad/glad.h>


namespace Utils {


static GLenum GetTextureTarget(bool isMultisampled)
{
    return isMultisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}


static bool IsDepthFormat(Zero::FramebufferTextureFormat format)
{
    switch (format)
    {
        case Zero::FramebufferTextureFormat::DEPTH24_STENCIL8:
        {
            return true;
        }

        default:
        {
            return false;
        }
    }
}


static void CreateTextures(bool isMultisampled, uint32_t* outID, uint32_t count)
{
    glCreateTextures(GetTextureTarget(isMultisampled), count, outID);
}


static void BindTexture(bool isMultisampled, uint32_t id)
{
    glBindTexture(GetTextureTarget(isMultisampled), id);
}


static void AttachColorTexture(uint32_t id, uint32_t samples, GLenum format, const glm::uvec2& size, int32_t index)
{
    const bool isMultisampled{ samples > 1u };

    if (isMultisampled)
    {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, size.x, size.y, GL_FALSE);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GetTextureTarget(isMultisampled), id, 0);
}


static void AttachDepthTexture(uint32_t id, uint32_t samples, GLenum format, GLenum attachmentType, const glm::uvec2& size)
{
    const bool isMultisampled{ samples > 1u };

    if (isMultisampled)
    {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, size.x, size.y, GL_FALSE);
    }
    else
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, format, size.x, size.y);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GetTextureTarget(isMultisampled), id, 0);
}


}


static constexpr uint32_t MAX_FRAMEBUFFER_SIZE{ 8192u };


Zero::FramebufferOpenGL::FramebufferOpenGL(const FramebufferProps& props) : m_Props{ props }
{
    for (const FramebufferTextureProps& attachment : m_Props.AttachmentProps.Attachments)
    {
        if (!Utils::IsDepthFormat(attachment.TextureFormat))
        {
            m_ColorAttachmentsProps.emplace_back(attachment);
        }
        else
        {
            m_DepthAttachmentProps = attachment;
        }
    }

    Invalidate();
}


Zero::FramebufferOpenGL::~FramebufferOpenGL()
{
    glDeleteFramebuffers(1, &m_RendererID);
    glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
    glDeleteTextures(1, &m_DepthAttachment);
}


void Zero::FramebufferOpenGL::Invalidate()
{
    if (m_RendererID)
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteTextures(1, &m_DepthAttachment);

        m_ColorAttachments.clear();
        m_DepthAttachment = 0u;
    }

    glCreateFramebuffers(1, &m_RendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

    const bool isMultisampled{ m_Props.Samples > 1u };

    if (m_ColorAttachmentsProps.size())
    {
        m_ColorAttachments.resize(m_ColorAttachmentsProps.size());
        Utils::CreateTextures(isMultisampled, m_ColorAttachments.data(), m_ColorAttachments.size());

        for (size_t i{ 0 }; i < m_ColorAttachments.size(); ++i)
        {
            Utils::BindTexture(isMultisampled, m_ColorAttachments[i]);

            switch (m_ColorAttachmentsProps[i].TextureFormat)
            {
                case FramebufferTextureFormat::RGBA8:
                {
                    Utils::AttachColorTexture(m_ColorAttachments[i], m_Props.Samples, GL_RGBA8, m_Props.Size, i);
                    break;
                }
            }
        }
    }

    if (m_DepthAttachmentProps.TextureFormat != FramebufferTextureFormat::None)
    {
        Utils::CreateTextures(isMultisampled, &m_DepthAttachment, 1u);
        Utils::BindTexture(isMultisampled, m_DepthAttachment);

        switch (m_DepthAttachmentProps.TextureFormat)
        {
            case FramebufferTextureFormat::DEPTH24_STENCIL8:
            {
                Utils::AttachDepthTexture(
                    m_DepthAttachment, m_Props.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Props.Size);
                break;
            }
        }
    }

    if (m_ColorAttachments.size() > 1)
    {
        ZR_CORE_ASSERT(m_ColorAttachments.size() <= 4, "");

        constexpr GLenum buffers[4]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers(m_ColorAttachments.size(), buffers);
    }
    else if (m_ColorAttachments.empty())
    {
        glDrawBuffer(GL_NONE);
    }

    ZR_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

    glBindFramebuffer(GL_FRAMEBUFFER, 0u);
}


void Zero::FramebufferOpenGL::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    glViewport(0, 0, m_Props.Size.x, m_Props.Size.y);
}


void Zero::FramebufferOpenGL::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0u);
}


void Zero::FramebufferOpenGL::Resize(const glm::uvec2& size)
{
    if (size.x == 0u || size.y == 0u || size.x > MAX_FRAMEBUFFER_SIZE || size.y > MAX_FRAMEBUFFER_SIZE)
    {
        ZR_CORE_WARN("Attempted to resize framebuffer to {}, {}", size.x, size.y);
        return;
    }

    m_Props.Size = size;
    Invalidate();
}


const Zero::FramebufferProps& Zero::FramebufferOpenGL::GetProps() const
{
    return m_Props;
}


const glm::uvec2& Zero::FramebufferOpenGL::GetSize() const
{
    return m_Props.Size;
}


uint32_t Zero::FramebufferOpenGL::GetColorAttachmentRendererID(uint32_t index) const
{
    ZR_CORE_ASSERT(index < m_ColorAttachments.size(), "");

    return m_ColorAttachments[index];
}
