#pragma once

struct GLFWwindow;

namespace ZY
{
	class Window
	{
	public:
		GLFWwindow* id;
		unsigned int width;
		unsigned int height;

	public:
		Window(unsigned int width, unsigned int height);
		~Window();

	public:
		bool isOpen() const;
		void update() const;

		// TODO: decouple events from windows
		void processEvents() const;

		void sendToSecondMonitor() const;

	private:
		void initializeGLFW() const;
		void create();

		inline static void errorCallback(int error, const char* description);
		inline static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}
