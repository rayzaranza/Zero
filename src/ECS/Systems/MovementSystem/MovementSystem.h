#pragma once 
#include "../../ECS.h"

namespace ZY
{
    class Movement : public System
    {
    public:
        Movement();

    public:
        void update() const;
    };
}
