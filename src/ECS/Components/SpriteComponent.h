#pragma once

#include "../../Logger/Logger.h"

namespace ZY
{
	struct SpriteComponent
	{
		float width;
		float height;

		SpriteComponent(float width = 1.0f, float height = 1.0f) :
			width{ width },
			height{ height }
		{
			LOG("Sprite componente created.");
		}
	};
}