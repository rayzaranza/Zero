#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

ZY::Camera::Camera(const Window& window, const glm::vec3& position) :
	position{ position },
	view{ 1.0f },
	projection{ 1.0f },
	fieldOfView{ 45.0f },
	window{ window }
{
	calculateMatrices();
}


void ZY::Camera::calculateMatrices()
{
	view = glm::translate(view, position);
	const float aspectRatio{ window.width / static_cast<float>(window.height) };
	projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.01f, 100.0f);
}
