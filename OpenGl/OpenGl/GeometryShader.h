#pragma once

#include "BaseShader.h"


class GeometryShader : public BaseShader
{
public:

	unsigned int createShaderProgram()
	{
		unsigned int geometryShader;
		const char* geometryShaderSource = m_shaderSource.c_str();
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		glCompileShader(geometryShader);

		//check if the compilation of the shader went through
		int success;
		char infoLog[512];
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return geometryShader;
	}



};
