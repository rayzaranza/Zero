#pragma once

#ifdef ZR_PLATFORM_WINDOWS

extern Zero::Application* Zero::CreateApplication();

int main(int argc, char** argv)
{
    Zero::Logger::Initialize();
    Zero::Application* application{ Zero::CreateApplication() };
    application->Run();
    delete application;
}

#endif
