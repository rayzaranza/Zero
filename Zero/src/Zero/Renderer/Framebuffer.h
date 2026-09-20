#pragma once
#include "Zero/Core/Core.h"

namespace Zero {

struct FramebufferProps {
  glm::uvec2 Size{ 1280u, 720u };
  uint32_t Samples{ 1u };
  bool SwapChainTarget{ false };
};

class Framebuffer {
public:
  virtual ~Framebuffer() = default;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual void Resize(const glm::vec2& size) = 0;
  virtual uint32_t GetColorAttachmentRendererID() const = 0;
  virtual const FramebufferProps& GetProps() const = 0;
  static Ref<Framebuffer> Create(const FramebufferProps& props);
};

}
