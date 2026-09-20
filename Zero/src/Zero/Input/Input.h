#pragma once
#include "KeyCode.h"
#include "MouseButton.h"

namespace Zero {

class Input {
public:
  static bool IsKeyPressed(const KeyCode keyCode);
  static bool IsMouseButtonPressed(const MouseButton button);
  static glm::vec2 GetMousePosition();
};

}
