#pragma once

namespace Zero
{
    //======================================================================================
    //  Vertex Attribute Type
    //======================================================================================

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

    //======================================================================================
    //  Vertex Attribute
    //======================================================================================

    uint32_t GetSizeFromAttributeType(AttributeType type);
    uint32_t GetComponentCountFromAttributeType(AttributeType type);

    struct VertexAttribute
    {
        std::string Name;
        AttributeType Type;
        uint32_t Size;
        uint32_t ComponentCount;
        bool IsNormalized;
        uint32_t Offset;

        VertexAttribute(AttributeType type, const std::string& name)
            : Name{name}
            , Type{type}
            , Size{GetSizeFromAttributeType(type)}
            , ComponentCount{GetComponentCountFromAttributeType(type)}
            , IsNormalized{false}
            , Offset{0}
        {}
    };

    //======================================================================================
    //  Vertex Buffer Layout
    //======================================================================================

    class VertexBufferLayout
    {
      public:
        VertexBufferLayout(const std::initializer_list<VertexAttribute>& attributes) : m_Attributes{attributes} { CalculateOffsetsAndStride(); }

      public:
        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<VertexAttribute>& GetAttributes() const { return m_Attributes; }

      public:
        inline std::vector<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
        inline std::vector<VertexAttribute>::iterator end() { return m_Attributes.end(); }
        inline std::vector<VertexAttribute>::const_iterator begin() const { return m_Attributes.begin(); }
        inline std::vector<VertexAttribute>::const_iterator end() const { return m_Attributes.end(); }

      private:
        void CalculateOffsetsAndStride();

      private:
        std::vector<VertexAttribute> m_Attributes;
        uint32_t m_Stride{};
    };

    //======================================================================================
    //  Vertex Buffer
    //======================================================================================

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

    //======================================================================================
    //  Index Buffer
    //======================================================================================

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
