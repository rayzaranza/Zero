#pragma once

#include "Zero/Renderer/Buffer.h"

namespace Zero
{
    class VertexArray
    {
      public:
      public:
        virtual ~VertexArray() = default;

      public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void AddVertexBuffer(const VertexBufferRef& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const IndexBufferRef& indexBuffer) = 0;
        virtual const Array<VertexBufferRef>& GetVertexBuffers() const = 0;
        virtual const IndexBufferRef& GetIndexBuffer() const = 0;

      public:
        static Ref<VertexArray> Create();
    };

    using VertexArrayRef = Ref<VertexArray>;
}
