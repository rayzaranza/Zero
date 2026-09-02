#pragma once

#ifdef ZERO_PLATFORM_WINDOWS

extern Zero::Application* Zero::CreateApplication();

int main(int argc, char** argv)
{
    Zero::Logger::Init();
    ZR_CORE_LOG("Test");
    ZR_LOG_WARN("Test from client");

    Zero::Application* application { Zero::CreateApplication() };
    application->Run();
    delete application;
}

#endif
