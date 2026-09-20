#pragma once

namespace Zero {
  class GraphicsContext {
  public:
    virtual ~GraphicsContext() = default;
    virtual void Initialize() = 0;
    virtual void SwapBuffers() = 0;
  };
}
