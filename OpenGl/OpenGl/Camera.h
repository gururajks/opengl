#pragma once

#include <glm.hpp>

class Camera
{
public:

	enum CameraDirection
	{
		Up,
		Down,
		Left,
		Right
	};

	Camera() {}

	Camera(glm::vec3 cameraPos, 
			glm::vec3 cameraTarget,
			glm::vec3 cameraUp) : cameraPos(cameraPos),
	   							  cameraTarget(cameraTarget),
								  cameraUp(cameraUp)
	{
		cameraFront = glm::vec3(0.0, 0.0, -1.0);
	}

	void updateCamera(glm::vec3 cameraPos,
		glm::vec3 cameraTarget,
		glm::vec3 cameraUp)
	{
		cameraPos = cameraPos;
		cameraTarget = cameraTarget;
		cameraUp = cameraUp;
	}

	void moveCamera(glm::vec3 distance, CameraDirection dir )
	{
		cameraPos += cameraFront + distance;
	}

	glm::mat4 viewMatrix()
	{
		return glm::lookAt(cameraPos, cameraTarget, cameraUp);
	}

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
};