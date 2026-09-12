#pragma once

#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class OpenGLRendererAPI : public RendererAPI
    {
      public:
        virtual void Initialize() override;
        virtual void SetClearColor(const Color& color) const override;
        virtual void Clear() const override;
        virtual void Clear(const Color& color) const override;
        virtual void DrawIndexed(const VertexArrayRef& vertexArray) override;
        virtual void SetViewport(const Vector2i& position, const Vector2u& size) override;
    };
}
