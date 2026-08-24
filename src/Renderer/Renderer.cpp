#include "../Logger/Logger.h"
#include "Renderer.h"

void ZY::Renderer::setViewport(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);
}

void ZY::Renderer::loadAPI(GLADloadproc addressCallback)
{
	gladLoadGLLoader((GLADloadproc)addressCallback);
	LOG("OpenGL loaded");
}

void ZY::Renderer::clear()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ZY::Renderer::draw(const VertexArray& vertexArray, const Shader& shader)
{
	shader.bind();
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, vertexArray.indicesCount, GL_UNSIGNED_INT, nullptr);
}