#pragma once

#ifdef ZERO_PLATFORM_WINDOWS

extern Zero::Application* Zero::CreateApplication();

int main(int argc, char** argv)
{
    Zero::Logger::Init();
    ZERO_CORE_LOG("Test");
    ZERO_WARN("Test from client");

    Zero::Application* application { Zero::CreateApplication() };
    application->Run();
    delete application;
}

#endif
