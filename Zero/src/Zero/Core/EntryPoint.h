#pragma once

#ifdef ZR_PLATFORM_WINDOWS

extern Zero::Application* Zero::CreateApplication();

int main(int argc, char** argv)
{
    Zero::Logger::Initialize();

    ZR_PROFILE_BEGIN_SESSION("Startup", "ZeroProfile.Startup.json");
    Zero::Application* application{ Zero::CreateApplication() };
    ZR_PROFILE_END_SESSION();

    ZR_PROFILE_BEGIN_SESSION("Runtime", "ZeroProfile.Runtime.json");
    application->Run();
    ZR_PROFILE_END_SESSION();

    ZR_PROFILE_BEGIN_SESSION("Shutdown", "ZeroProfile.Shutdown.json");
    delete application;
    ZR_PROFILE_END_SESSION();
}

#endif
