#pragma once

#include "../../../Buffer/VertexArray.h"
#include "../../../Shader/Shader.h"
#include "../../ECS.h"

namespace ZY
{
    class RenderSystem : public System
    {
    public:
        RenderSystem();

    public:
        void draw(const VertexArray& vertexArray, const Shader& shader) const;
    };
}
