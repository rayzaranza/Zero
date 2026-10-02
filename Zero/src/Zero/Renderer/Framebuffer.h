#pragma once
#include "Zero/Core/Core.h"


namespace Zero {


enum class FramebufferTextureFormat : uint8_t
{
    None,
    RGBA8,
    DEPTH24_STENCIL8,
    Depth = DEPTH24_STENCIL8,
};


struct FramebufferTextureProps
{
    FramebufferTextureFormat TextureFormat{ FramebufferTextureFormat::None };

    FramebufferTextureProps() = default;
    FramebufferTextureProps(FramebufferTextureFormat format);
};


struct FramebufferAttachmentProps
{
    Array<FramebufferTextureProps> Attachments{};

    FramebufferAttachmentProps() = default;
    FramebufferAttachmentProps(std::initializer_list<FramebufferTextureProps> attachments);
};


struct FramebufferProps
{
    glm::uvec2 Size{ 1280u, 720u };
    FramebufferAttachmentProps AttachmentProps;
    uint32_t Samples{ 1u };
    bool SwapChainTarget{ false };
};


class Framebuffer
{
  public:
    virtual ~Framebuffer() = default;

  public:
    static Ref<Framebuffer> Create(const FramebufferProps& props);

  public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void Resize(const glm::uvec2& size) = 0;
    virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0u) const = 0;
    virtual const FramebufferProps& GetProps() const = 0;
    virtual const glm::uvec2& GetSize() const = 0;
};


}
