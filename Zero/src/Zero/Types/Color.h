#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    struct Color : public glm::vec4
    {
        using glm::vec4::vec4;

        static Color White;
        static Color Black;
        static Color Gray;
        static Color Red;
        static Color Green;
        static Color Blue;
        static Color Magenta;
        static Color Yellow;
        static Color Transparent;
    };

    inline Color Color::Red{ 1.0f, 0.0f, 0.0f, 1.0f };
    inline Color Color::White{ 1.0f, 1.0f, 1.0f, 1.0f };
    inline Color Color::Black{ 0.0f, 0.0f, 0.0f, 1.0f };
    inline Color Color::Gray{ 0.5f, 0.5f, 0.5f, 1.0f };
    inline Color Color::Green{ 0.0f, 1.0f, 0.0f, 1.0f };
    inline Color Color::Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
    inline Color Color::Magenta{ 1.0f, 0.0f, 1.0f, 1.0f };
    inline Color Color::Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
    inline Color Color::Transparent{ 0.0f, 0.0f, 0.0f, 0.0f };
}
