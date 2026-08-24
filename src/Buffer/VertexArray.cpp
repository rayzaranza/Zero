#include "../Logger/Logger.h"
#include "VertexArray.h"
#include <glad/glad.h>


ZY::VertexArray::VertexArray()
	: indicesCount{ 0 }
{
	glGenVertexArrays(1, &id);
	LOG("Vertex Array #{} created.", id);
}

ZY::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
	LOG("Vertex Array #{} destroyed.", id);
}

void ZY::VertexArray::bind() const
{
	glBindVertexArray(id);
}

void ZY::VertexArray::addBuffer(const VertexBuffer& buffer, const IndexBuffer& indexBuffer)
{
	bind();
	buffer.bind();
	indexBuffer.bind();
	indicesCount = indexBuffer.count;

	for (unsigned int i{ 0 }; i < buffer.attributes.size(); ++i)
	{
		const VertexAttribute& attribute = buffer.attributes[i];
		const unsigned int location{ i };
		const void* offset{ (const void*)(sizeof(float) * attribute.count * location) };
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, attribute.count, attribute.type, GL_FALSE, buffer.stride, offset);
	}
}
