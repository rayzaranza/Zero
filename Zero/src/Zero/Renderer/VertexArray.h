#pragma once

#include "Zero/Renderer/Buffer.h"

namespace Zero
{
    class VertexArray;
    using VertexArrayRef = Ref<VertexArray>;

    class VertexArray
    {
      public:
      public:
        virtual ~VertexArray() = default;

      public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
        virtual const Array<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

      public:
        static VertexArrayRef Create();
    };

}
