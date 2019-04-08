#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class CubeVertexBuffer
{

	;
public:
	CubeVertexBuffer(unsigned int VAO[], unsigned int VBO[])
	{
		glGenVertexArrays(2, VAO);
		glGenBuffers(2, VBO);
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(graphics::cubeVertices), graphics::cubeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

};
