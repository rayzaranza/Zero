#pragma once
#include "Zero/Core/Core.h"

namespace Zero {
  struct FramebufferProps {
    uint32_t Width{ 1280u };
    uint32_t Height{ 1280u };
    uint32_t Samples{ 1u };
    bool SwapChainTarget{ false };
  };

  class Framebuffer {
  public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual uint32_t GetColorAttachmentRendererID() const = 0;
    virtual const FramebufferProps& GetProps() const = 0;
    static Ref<Framebuffer> Create(const FramebufferProps& props);
  };
}
