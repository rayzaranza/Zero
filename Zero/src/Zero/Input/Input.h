#pragma once

#include "Zero/Input/KeyCode.h"
#include "Zero/Input/MouseButton.h"

namespace Zero
{
    class Input
    {
      public:
        static bool IsKeyPressed(const KeyCode keyCode);
        static bool IsMouseButtonPressed(const MouseButton button);
        static glm::vec2 GetMousePosition();

      private:
        static Input* s_Instance;
    };
}
