#include "Application.h"

#include <print>

namespace Zero
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		std::println("Teste");
		while (true);
	}
}