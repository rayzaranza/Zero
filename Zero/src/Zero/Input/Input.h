#pragma once

#include "Zero/Input/KeyCode.h"
#include "Zero/Input/MouseButton.h"

#include <glm/glm.hpp>

namespace Zero
{
    class Input
    {
      public:
        static Boolean IsKeyPressed(const KeyCode keyCode);
        static Boolean IsMouseButtonPressed(const MouseButton button);
        static Vector2 GetMousePosition();

      private:
        static Input* s_Instance;
    };
}
