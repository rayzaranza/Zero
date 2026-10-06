#include "Application.h"
#include "../Logger/Logger.h"


namespace Zero {


Application::Application() : m_Window { CreateScope<Window>() }
{
}


Application::~Application()
{
    Z_LOG("Application destroyed");
}


void Application::Run() const
{
    while (m_IsRunning)
    {
        m_Window->Update();
    }
}


}
