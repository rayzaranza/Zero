#pragma once

#include "Zero/Renderer/RendererAPI.h"

namespace Zero
{
    class OpenGLRendererAPI : public RendererAPI
    {
      public:
        virtual void Initialize() override;
        virtual void SetClearColor(const glm::vec4& color) const override;
        virtual void Clear() const override;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}
