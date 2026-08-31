#pragma once

#include "Core.h"

namespace Zero
{
	class ZERO_API Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		void Run();

	};

	Application* CreateApplication();
}