#include "Sandbox.h"

#include <Zero/EntryPoint.h>

Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
