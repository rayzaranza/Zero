#include <memory>
#include "Application/Application.h"


int main()
{
    const auto application { Zero::CreateScope<Zero::Application>() };
    application->Run();
}
