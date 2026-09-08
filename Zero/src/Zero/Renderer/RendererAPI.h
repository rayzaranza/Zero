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
        virtual void SetClearColor(const glm::vec4& color) const = 0;
        virtual void Clear() const = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

      public:
        inline static API GetAPI() { return s_API; }

      private:
        static API s_API;
    };

}
