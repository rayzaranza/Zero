#include "Window.h"
#define GLFW_INCLUDE_NONE
#include "../Logger/Logger.h"
#include "../Renderer/Renderer.h"
#include <GLFW/glfw3.h>


ZY::Window::Window(unsigned int width, unsigned int height) :
	width{ width },
	height{ height }
{
	initializeGLFW();
	create();
	LOG("Window created.");
}

ZY::Window::~Window()
{
	glfwDestroyWindow(id);
	glfwTerminate();
	LOG("Window destroyed.");
}

bool ZY::Window::isOpen() const
{
	return !glfwWindowShouldClose(id);
}

void ZY::Window::processEvents() const
{
	glfwPollEvents();
}

void ZY::Window::update() const
{
	glfwSwapBuffers(id);
	glfwSwapInterval(1);
}

void ZY::Window::initializeGLFW() const
{
	glfwSetErrorCallback(errorCallback);
	const int initStatus{ glfwInit() };
	if (initStatus == GLFW_FALSE)
	{
		LOG_CRITICAL("Error initializing GLFW.");
	}
}

void ZY::Window::create()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	id = glfwCreateWindow(width, height, "", nullptr, nullptr);
	if (id == NULL)
	{
		LOG_CRITICAL("Error creating GLFW window");
		glfwTerminate();
	}

	glfwMakeContextCurrent(id);
	glfwSetFramebufferSizeCallback(id, framebufferSizeCallback);
	glfwSetErrorCallback(errorCallback);

	ZY::Renderer::loadAPI((GLADloadproc)glfwGetProcAddress);
}

inline void ZY::Window::errorCallback(int error, const char* description)
{
	LOG_ERROR(description);
}

inline void ZY::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	ZY::Renderer::setViewport(width, height);
}
