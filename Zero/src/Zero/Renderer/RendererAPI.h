#pragma once

#include "Zero/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Zero
{
    class RendererAPI
    {
      public:
        enum class API
        {
            None,
            OpenGL,
            Vulkan,
        };

      public:
        virtual void Initialize() = 0;
        virtual void SetClearColor(const Color& color) const = 0;
        virtual void Clear() const = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
        virtual void SetViewport(I32 x, I32 y, U32 width, U32 height) = 0;

      public:
        inline static API GetAPI() { return s_API; }

      private:
        static API s_API;
    };

}
