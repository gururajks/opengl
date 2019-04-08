#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"
#include "GeometryShader.h"
#include<memory>
#include<set>

using namespace std;

class Shader
{
	set<unsigned int> registerShader;
	unsigned int shaderProgram;
public:
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geomeotryShaderFile)
	{
		unique_ptr<BaseShader> vertexShaderPtr = make_unique<VertexShader>();
		vertexShaderPtr->readFile(vertexShaderFile);
		unsigned int vertexShader = vertexShaderPtr->createShaderProgram();
		registerShader.insert(vertexShader);

		unique_ptr<BaseShader> fragShaderPtr = make_unique<FragmentShader>();
		fragShaderPtr->readFile(fragmentShaderFile);
		unsigned int fragmentShader = fragShaderPtr->createShaderProgram();
		registerShader.insert(fragmentShader);

		unique_ptr<BaseShader> geometryShaderPtr = make_unique<GeometryShader>();
		geometryShaderPtr->readFile(geomeotryShaderFile);
		unsigned int geometryShader = geometryShaderPtr->createShaderProgram();
		registerShader.insert(geometryShader);
	}

	unsigned int linkShader()
	{		
		shaderProgram = glCreateProgram();
		for (auto item : registerShader)
		{
			glAttachShader(shaderProgram, item);
		}
		
		glLinkProgram(shaderProgram);
		int success;
		char infoLog[512];
		glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		for (auto item : registerShader)
		{
			glDeleteShader(item);
		}
		return shaderProgram;
	}


	void setShaderUniform(std::string key, glm::mat4 tMatrix)
	{
		unsigned int f1transformLoc = glGetUniformLocation(shaderProgram, key.c_str());
		glUniformMatrix4fv(f1transformLoc, 1, GL_FALSE, glm::value_ptr(tMatrix));
	}


};