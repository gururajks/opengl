#pragma once

#include "BaseShader.h"


class FragmentShader : public BaseShader
{
public:

	unsigned int createShaderProgram()
	{
		unsigned int vertexShader;		
		const char* vertexShaderSource = m_shaderSource.c_str();
		vertexShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		//check if the compilation of the shader went through
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return vertexShader;
	}



};
