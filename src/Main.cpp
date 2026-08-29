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

	while (window.isOpen())
	{
		window.processEvents();

		ZY::Renderer::clear();

		registry.getSystem<ZY::Movement>().update();
		registry.update();

		window.update();
	}
}