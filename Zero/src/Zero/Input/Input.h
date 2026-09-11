#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class Input
    {
      public:
        static Boolean IsKeyPressed(I32 keyCode);
        static Boolean IsMouseButtonPressed(I32 button);
        static Vector2 GetMousePosition();

      private:
        static Input* s_Instance;
    };
}
