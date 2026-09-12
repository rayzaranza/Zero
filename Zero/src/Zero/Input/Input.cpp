#include "Zero/Input/Input.h"

#include <GLFW/glfw3.h>

#include "Zero/Application/Application.h"

namespace Zero
{
    Input* Input::s_Instance{ new Input() };

    Boolean Input::IsKeyPressed(const KeyCode keyCode)
    {
        GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
        const I32 state{ glfwGetKey(window, static_cast<I32>(keyCode)) };
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    Boolean Input::IsMouseButtonPressed(const MouseButton button)
    {
        GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
        const I32 state{ glfwGetMouseButton(window, static_cast<I32>(button)) };
        return state == GLFW_PRESS;
    }

    Vector2 Input::GetMousePosition()
    {
        GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
        F64 x, y;
        glfwGetCursorPos(window, &x, &y);
        return Vector2{ static_cast<F32>(x), static_cast<F32>(y) };
    }

}
