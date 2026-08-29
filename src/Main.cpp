#include "Main.h"

int main(int argc, char* argv[])
{
    ZY::Logger::init();

    ZY::Window window { 1800, 960 };

    ZY::VertexAttribute attribute { .count { 2 }, .type { GL_FLOAT } };

    int x { 5 };
    float v { 0.0f };
    double wage {};

    while (window.isOpen())
    {
        window.processEvents();

        ZY::Renderer::clear();
        window.update();
    }
}
