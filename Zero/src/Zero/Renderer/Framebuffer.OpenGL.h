#pragma once
#include "Framebuffer.h"

namespace Zero {

class FramebufferOpenGL : public Framebuffer {
public:
  FramebufferOpenGL(const FramebufferProps& framebuffer);
  virtual ~FramebufferOpenGL();
  virtual void Bind() const override;
  virtual void Unbind() const override;
  virtual void Resize(const glm::uvec2& size) override;
  virtual const FramebufferProps& GetProps() const override;
  virtual uint32_t GetColorAttachmentRendererID() const override;
  void Invalidate();

private:
  uint32_t m_RendererID{};
  uint32_t m_ColorAttachment{};
  uint32_t m_DepthAttachment{};
  FramebufferProps m_Props;
};

}
