#include "Application.h"
#include "../Logger/Logger.h"


Zero::Application::Application() : m_Window { Window::Create({ "Zero", { 1920, 1080 } }) }
{
    Z_LOG("Application created");
}


Zero::Application::~Application()
{
    Z_LOG("Application destroyed");
}


void Zero::Application::Run() const
{
    while (m_IsRunning)
    {
        m_Window->Update();
    }
}
