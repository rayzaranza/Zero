#pragma once

#ifdef ZERO_PLATFORM_WINDOWS

extern Zero::Application* Zero::CreateApplication();

int main(int argc, char** argv)
{
	Zero::Application* application{ Zero::CreateApplication() };
	application->Run();
	delete application;
}

#endif