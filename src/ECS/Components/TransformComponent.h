#pragma once

#include "../../Logger/Logger.h"
#include <glm/glm.hpp>

namespace ZY
{
	struct TransformComponent
	{
		glm::vec2 position;
		glm::vec2 scale;
		double rotation;

		TransformComponent(
			const glm::vec2& position = glm::vec2{ 0.0f },
			const glm::vec2& scale = glm::vec2{ 1.0f },
			double rotation = 0.0
		) :
			position{ position },
			scale{ scale },
			rotation{ rotation }
		{
			LOG("Transform component created.");
		}
	};
}

