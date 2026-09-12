#pragma once

#include "Zero/Core/Core.h"

namespace Zero
{
    //======================================================================================
    //  Vertex Attribute Type
    //======================================================================================
    enum class AttributeType : U8
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
    I32 GetSizeFromAttributeType(const AttributeType type);
    U32 GetComponentCountFromAttributeType(const AttributeType type);

    struct VertexAttribute
    {
        String Name;
        AttributeType Type;
        I32 Size;
        U32 ComponentCount;
        Boolean IsNormalized;
        U32 Offset;

        VertexAttribute(const AttributeType type, const String& name)
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
        inline U32 GetStride() const { return m_Stride; }
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
        U32 m_Stride{};
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
        static Ref<VertexBuffer> Create(const Array<F32>& vertices);
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
        virtual Length GetLength() const = 0;

      public:
        static Ref<IndexBuffer> Create(const Array<U32>& indices);
    };

    using IndexBufferRef = Ref<IndexBuffer>;
}
