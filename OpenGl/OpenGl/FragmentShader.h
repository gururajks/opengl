#pragma once

#include "BaseShader.h"


class FragmentShader : public BaseShader
{
public:

	unsigned int createShaderProgram()
	{
		unsigned int fragShader;		
		const char* fragShaderSource = m_shaderSource.c_str();
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragShaderSource, NULL);
		glCompileShader(fragShader);

		//check if the compilation of the shader went through
		int success;
		char infoLog[512];
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return fragShader;
	}



};
