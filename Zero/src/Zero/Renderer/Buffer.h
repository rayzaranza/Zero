#pragma once

#include "Zero/Core/Core.h"

namespace Zero
{
    //======================================================================================
    //  Vertex Attribute Type
    //======================================================================================
    enum class AttributeType : uint8_t
    {
        Float,
        Vector2,
        Vector3,
        Vector4,
        Matrix3,
        Matrix4,
        Int,
        Vector2i,
        Vector3i,
        Vector4i,
        Boolean,
    };

    //======================================================================================
    //  Vertex Attribute
    //======================================================================================
    int32_t GetSizeFromAttributeType(const AttributeType type);
    uint32_t GetComponentCountFromAttributeType(const AttributeType type);

    struct VertexAttribute
    {
        std::string Name;
        AttributeType Type;
        int32_t Size;
        uint32_t ComponentCount;
        bool IsNormalized;
        uint32_t Offset;

        VertexAttribute(const AttributeType type, const std::string& name)
            : Name{ name }
            , Type{ type }
            , Size{ GetSizeFromAttributeType(type) }
            , ComponentCount{ GetComponentCountFromAttributeType(type) }
            , IsNormalized{ false }
            , Offset{ 0 }
        {}
    };

    //======================================================================================
    //  Vertex Buffer Layout
    //======================================================================================
    class VertexBufferLayout
    {
      public:
        VertexBufferLayout(const std::initializer_list<VertexAttribute>& attributes) : m_Attributes{ attributes }
        {
            CalculateOffsetsAndStride();
        }

      public:
        inline uint32_t GetStride() const { return m_Stride; }
        inline const Array<VertexAttribute>& GetAttributes() const { return m_Attributes; }

      public:
        inline Array<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
        inline Array<VertexAttribute>::iterator end() { return m_Attributes.end(); }
        inline Array<VertexAttribute>::const_iterator begin() const { return m_Attributes.begin(); }
        inline Array<VertexAttribute>::const_iterator end() const { return m_Attributes.end(); }

      private:
        void CalculateOffsetsAndStride();

      private:
        Array<VertexAttribute> m_Attributes;
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
        virtual void SetData(const void* data, const uint32_t size) = 0;
        virtual void SetLayout(const VertexBufferLayout& layout) = 0;
        virtual const VertexBufferLayout& GetLayout() const = 0;

      public:
        static Ref<VertexBuffer> Create(const Array<float>& vertices);
        static Ref<VertexBuffer> Create(const uint32_t size);
    };

    using VertexBufferRef = Ref<VertexBuffer>;

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
        virtual size_t GetLength() const = 0;

      public:
        static Ref<IndexBuffer> Create(const uint32_t size);
        static Ref<IndexBuffer> Create(const uint32_t* indices, const uint32_t size);
        static Ref<IndexBuffer> Create(const Array<uint32_t>& indices);
    };

    using IndexBufferRef = Ref<IndexBuffer>;
}
