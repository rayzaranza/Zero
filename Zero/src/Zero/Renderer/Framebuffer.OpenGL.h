#pragma once
#include "Zero/Renderer/Framebuffer.h"


namespace Zero {


class FramebufferOpenGL : public Framebuffer
{
  public:
    FramebufferOpenGL(const FramebufferProps& framebuffer);
    virtual ~FramebufferOpenGL();

  public:
    void Invalidate();
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void Resize(const glm::uvec2& size) override;
    virtual const FramebufferProps& GetProps() const override;
    virtual const glm::uvec2& GetSize() const override;
    virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0u) const override;

  private:
    uint32_t m_RendererID{};
    FramebufferProps m_Props;
    Array<FramebufferTextureProps> m_ColorAttachmentsProps{};
    FramebufferTextureProps m_DepthAttachmentProps{ FramebufferTextureFormat::None };
    Array<uint32_t> m_ColorAttachments{};
    uint32_t m_DepthAttachment{};
};


}
