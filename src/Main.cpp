#include "Main.h"

int main(int argc, char* argv[])
{

	ZY::Logger::init();

	ZY::Window window{ 1800, 960 };

	ZY::Registry registry;

	ZY::Entity truck{ registry.createEntity() };
	ZY::Entity tank{ registry.createEntity() };

	truck.addComponent<ZY::TransformComponent>();
	truck.addComponent<ZY::RigidBodyComponent>(glm::vec2{ 0.0f, 1.0f });

	registry.addSystem<ZY::Movement>();

	window.sendToSecondMonitor();

	ZY::Camera camera{ window, glm::vec3(0.0f, 0.0f, -1.5f) };

	ZY::VertexBuffer quadVertexBuffer{ {
		 0.5f,  0.5f,	1.0f, 1.0f,
		 0.5f, -0.5f,	1.0f, 0.0f,
		-0.5f, -0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f,	0.0f, 1.0f
	} };

	quadVertexBuffer.setAttributes({ { 2 }, { 2 } });

	ZY::IndexBuffer quadIndexBuffer{ { 0, 1, 3, 1, 2, 3 } };
	ZY::VertexArray quadVertexArray;
	quadVertexArray.addBuffer(quadVertexBuffer, quadIndexBuffer);

	ZY::Shader defaultShader{ "default" };
	defaultShader.setUniform("u_Color", glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	defaultShader.setUniform("u_View", camera.view);
	defaultShader.setUniform("u_Projection", camera.projection);

	while (window.isOpen())
	{
		window.processEvents();
		ZY::Renderer::clear();
		ZY::Renderer::draw(quadVertexArray, defaultShader);
		registry.getSystem<ZY::Movement>().update();
		registry.update();
		window.update();
	}
}