#include "Input.h"
#include "Zero/Application/Application.h"
#include <GLFW/glfw3.h>

bool Zero::Input::IsKeyPressed(const KeyCode keyCode) {
  GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
  const int32_t state{ glfwGetKey(window, static_cast<int32_t>(keyCode)) };
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Zero::Input::IsMouseButtonPressed(const MouseButton button) {
  GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
  const int32_t state{ glfwGetMouseButton(window, static_cast<int32_t>(button)) };
  return state == GLFW_PRESS;
}

glm::vec2 Zero::Input::GetMousePosition() {
  GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
}
