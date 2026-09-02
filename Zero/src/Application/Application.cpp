#include "Application.h"
#include "Events/ApplicationEvent/ApplicationEvent.h"
#include "Logger/Logger.h"

namespace Zero
{
    Application::Application()
    {}

    Application::~Application()
    {}

    void Application::Run()
    {
        WindowResizedEvent event { 1280, 720 };
        ZR_LOG(event);

        while (true);
    }
}
