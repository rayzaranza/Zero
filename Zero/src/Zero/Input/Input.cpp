#include "Input.h"

#include <GLFW/glfw3.h>

#include "Zero/Application/Application.h"

namespace Zero
{
    Input* Input::s_Instance{new Input()};

    bool Input::IsKeyPressed(int keyCode)
    {
        GLFWwindow* window{Application::Get().GetWindow().GetWindowHandle()};
        const int state{glfwGetKey(window, keyCode)};
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        GLFWwindow* window{Application::Get().GetWindow().GetWindowHandle()};
        const int state{glfwGetMouseButton(window, button)};
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        GLFWwindow* window{Application::Get().GetWindow().GetWindowHandle()};
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2{static_cast<float>(x), static_cast<float>(y)};
    }

}
