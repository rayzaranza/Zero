#include "Application/Application.h"
#include "Logger/Logger.h"


int main()
{
    Zero::Logger::Init();

    Zero::Application* application { new Zero::Application {} };
    application->Run();

    delete application;
}
