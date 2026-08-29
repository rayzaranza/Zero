#include "../Logger/Logger.h"
#include "IndexBuffer.h"

ZY::IndexBuffer::IndexBuffer(const IndexBufferData& data, GLenum usage)
    : count { static_cast<unsigned int>(data.size()) }
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), usage);

    LOG("Index Buffer #{} created.", id);
}

ZY::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id);
    LOG("Index Buffer #{} destroyed.", id);
}

void ZY::IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
