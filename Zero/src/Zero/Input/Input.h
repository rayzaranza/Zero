#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class Input
    {
      public:
        static bool IsKeyPressed(int keyCode);
        static bool IsMouseButtonPressed(int button);
        static glm::vec2 GetMousePosition();

      private:
        static Input* s_Instance;
    };
}
