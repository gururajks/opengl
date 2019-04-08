#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

class BaseShader
{
public:
	BaseShader() : m_shaderSource("") {}

	const char* getShaderSource()
	{
		return m_shaderSource.c_str();
	}

	void readFile(const char *filePath) {
		std::ifstream fileStream(filePath, std::ios::in);

		if (!fileStream.is_open()) {
			std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			m_shaderSource.append(line + "\n");
		}

		fileStream.close();
		m_shaderSource += "\0";
	}

	virtual unsigned int createShaderProgram() = 0;

protected:
	std::string		m_shaderSource;


};
