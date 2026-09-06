#pragma once

namespace Zero
{
    // ················································································································
    //  Vertex Buffer
    // ················································································································

    class VertexBuffer
    {
      public:
        virtual ~VertexBuffer() = default;

      public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

      public:
        static VertexBuffer* Create(float* vertices, size_t size);
    };

    // ················································································································
    //  Index Buffer
    // ················································································································

    class IndexBuffer
    {
      public:
        virtual ~IndexBuffer() = default;

      public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetCount() const = 0;

      public:
        static IndexBuffer* Create(uint32_t* indices, size_t size);
    };
}
