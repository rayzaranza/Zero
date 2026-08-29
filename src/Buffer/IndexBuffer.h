#pragma once
#include <glad/glad.h>
#include <vector>

namespace ZY
{
    using IndexBufferData = std::vector<unsigned int>;

    class IndexBuffer
    {
    private:
        unsigned int id;

    public:
        unsigned int count;

    public:
        IndexBuffer(const IndexBufferData& data, GLenum usage = GL_STATIC_DRAW);
        ~IndexBuffer();

        void bind() const;
    };
}
