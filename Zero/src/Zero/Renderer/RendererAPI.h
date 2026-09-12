#pragma once

#include "Zero/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Zero
{
    class RendererAPI
    {
      public:
        enum class API : U8
        {
            None,
            OpenGL,
            Vulkan,
        };

      public:
        virtual void Initialize() = 0;
        virtual void SetClearColor(const Color& color) const = 0;
        virtual void Clear() const = 0;
        virtual void DrawIndexed(const VertexArrayRef& vertexArray) = 0;
        virtual void SetViewport(const Vector2i& position, const Vector2u& size) = 0;

      public:
        inline static API GetAPI() { return s_API; }

      private:
        static API s_API;
    };

}
