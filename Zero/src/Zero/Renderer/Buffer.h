#pragma once

namespace Zero
{
    // ················································································································
    //  Vertex Attribute Type
    // ················································································································

    enum class AttributeType : uint8_t
    {
        Float,
        Float2,
        Float3,
        Float4,
        Matrix3,
        Matrix4,
        Int,
        Int2,
        Int3,
        Int4,
        Boolean,
    };

    // ················································································································
    //  Vertex Attribute
    // ················································································································

    struct VertexAttribute
    {
        std::string Name {};
        uint32_t Size {};
        uint32_t Offset {};
        AttributeType Type {};
        uint32_t ComponentCount {};
        bool IsNormalized {};

        VertexAttribute(AttributeType type, const std::string& name);
    };

    // ················································································································
    //  Vertex Buffer Layout
    // ················································································································

    class VertexBufferLayout
    {
      public:
        VertexBufferLayout(const std::initializer_list<VertexAttribute>& attributes);

      public:
        uint32_t GetStride() const;
        const std::vector<VertexAttribute>& GetAttributes() const;

      public:
        std::vector<VertexAttribute>::iterator begin();
        std::vector<VertexAttribute>::iterator end();
        std::vector<VertexAttribute>::const_iterator begin() const;
        std::vector<VertexAttribute>::const_iterator end() const;

      private:
        void CalculateOffsetsAndStride();

      private:
        std::vector<VertexAttribute> m_Attributes {};
        uint32_t m_Stride {};
    };

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
        virtual void SetLayout(const VertexBufferLayout& layout) = 0;
        virtual const VertexBufferLayout& GetLayout() const = 0;

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
