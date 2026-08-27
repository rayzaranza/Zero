#pragma once
#include "../../Logger/Logger.h"
#include <glm/glm.hpp>

namespace ZY
{
	struct RigidBodyComponent
	{
		glm::vec2 velocity;

		RigidBodyComponent(const glm::vec2& velocity = glm::vec2(0.0f))
			: velocity{ velocity }
		{
			LOG("RigidBody component created.");
		}
	};
}