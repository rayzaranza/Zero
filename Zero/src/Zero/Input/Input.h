#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class Input
    {
      public:
        static Boolean IsKeyPressed(const I32 keyCode);
        static Boolean IsMouseButtonPressed(const I32 button);
        static const Vector2& GetMousePosition();

      private:
        static Input* s_Instance;
    };
}
