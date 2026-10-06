#include "Application.h"
#include "../Logger/Logger.h"


Zero::Application::Application() : m_Window { CreateScope<Window>() }
{
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
