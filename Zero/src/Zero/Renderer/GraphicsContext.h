#pragma once


namespace Zero {


class GraphicsContext
{
  public:
    virtual ~GraphicsContext() = default;

  public:
    virtual void Initialize() = 0;
    virtual void SwapBuffers() = 0;
};


}
