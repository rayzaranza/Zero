#pragma once
#include "../Window/Window.h"
#include <glm/glm.hpp>

namespace ZY
{
    class Camera
    {
    public:
        glm::vec3 position;
        glm::mat4 view;
        glm::mat4 projection;
        const Window& window;
        float fieldOfView;

    public:
        Camera(const Window& window, const glm::vec3& position = { 0.0f, 0.0f, -6.0f });

    private:
        void calculateMatrices();
    };
}
