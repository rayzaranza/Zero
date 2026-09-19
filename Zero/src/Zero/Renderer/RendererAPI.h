#pragma once

#include "Zero/Renderer/VertexArray.h"

namespace Zero
{
    class RendererAPI
    {
      public:
        enum class API : uint8_t
        {
            None,
            OpenGL,
            Vulkan,
        };

      public:
        virtual void Initialize() = 0;
        virtual void SetClearColor(const glm::vec4& color) const = 0;
        virtual void Clear() const = 0;
        virtual void Clear(const glm::vec4& color) const = 0;
        virtual void DrawIndexed(const VertexArrayRef& vertexArray, const uint32_t indexCount) = 0;
        virtual void SetViewport(const glm::ivec2& position, const glm::uvec2& size) = 0;

      public:
        inline static API GetAPI() { return s_API; }
        static Scope<RendererAPI> Create();

      private:
        static API s_API;
    };

}
