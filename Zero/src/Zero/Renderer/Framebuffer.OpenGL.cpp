#include "Framebuffer.OpenGL.h"
#include <glad/glad.h>

Zero::FramebufferOpenGL::FramebufferOpenGL(const FramebufferProps& props) : m_Props{ props } {
  Invalidate();
}

Zero::FramebufferOpenGL::~FramebufferOpenGL() {
  glDeleteFramebuffers(1, &m_RendererID);
}

void Zero::FramebufferOpenGL::Bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void Zero::FramebufferOpenGL::Unbind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0u);
}

const Zero::FramebufferProps& Zero::FramebufferOpenGL::GetProps() const {
  return m_Props;
}

uint32_t Zero::FramebufferOpenGL::GetColorAttachmentRendererID() const {
  return m_ColorAttachment;
}

void Zero::FramebufferOpenGL::Invalidate() {
  glCreateFramebuffers(1, &m_RendererID);
  glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
  glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Props.Width, m_Props.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
  glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Props.Width, m_Props.Height);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

  const bool isFramebufferComplete{ glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE };
  ZR_CORE_ASSERT(isFramebufferComplete, "Framebuffer is incomplete");

  glBindFramebuffer(GL_FRAMEBUFFER, 0u);
}
