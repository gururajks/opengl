#pragma once

#include <glm.hpp>

class Camera
{
public:
	Camera() {}

	Camera(glm::vec3 cameraPos, 
			glm::vec3 cameraTarget,
			glm::vec3 cameraUp) : cameraPos(cameraPos),
	   							  cameraTarget(cameraTarget),
								  cameraUp(cameraUp)
	{}

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
};