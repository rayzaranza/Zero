#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace ZY
{
    class VertexArray
    {
    private:
        unsigned int id;

    public:
        unsigned int indicesCount;

    public:
        VertexArray();
        ~VertexArray();

        inline void bind() const;

        void addBuffer(const VertexBuffer& buffer, const IndexBuffer& indexBuffer);
    };
}
