#pragma once
#include <glad/glad.h>
#include <vector>

namespace ZY
{
    // TODO: accept other data types
    // should i create a global vertex struct?
    using VertexBufferData = std::vector<float>;

    struct VertexAttribute
    {
        unsigned int count {};
        GLenum type {};
    };

    using VertexBufferLayout = std::vector<VertexAttribute>;

    class VertexBuffer
    {
    private:
        unsigned int id;

    public:
        unsigned int stride;
        VertexBufferLayout attributes;

    public:
        VertexBuffer(const VertexBufferData& data, GLenum usage = GL_STATIC_DRAW);
        ~VertexBuffer();

        inline void bind() const;
        void setAttributes(const VertexBufferLayout& attributes);

    private:
        void calculateStride();
    };
}
