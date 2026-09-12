#include "Sandbox.h"

#include <Zero/Core/EntryPoint.h>

Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
