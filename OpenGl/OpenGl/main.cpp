#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include "ShaderReader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int SCR_WIDTH = 600;
int SCR_HEIGHT = 800;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
        -0.4f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.6f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.2f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    float secondVertices[] = {
        0.9f, 0.5f, 0.0f,
        0.5f, 0.0, 0.0f,
        0.9f, -0.5f, 0.0f
    };    

	ShaderReader vSRead;
	vSRead.readFile("E:\\opengl\\OpenGl\\OpenGl\\vertexshader.glsl");
	const char* vertexShaderSource = vSRead.getShaderSource();

	ShaderReader fSRead;
	fSRead.readFile("E:\\opengl\\OpenGl\\OpenGl\\fragshader.glsl");
	const char* fragmentShaderSource = fSRead.getShaderSource();

	ShaderReader fSRead2;
	fSRead2.readFile("E:\\opengl\\OpenGl\\OpenGl\\secondfragshader.glsl");
	const char* secondFragmentShaderSource = fSRead2.getShaderSource();
	    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //check if the compilation of the shader went through
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int secondFragmentShader;
    secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(secondFragmentShader, 1, &secondFragmentShaderSource, NULL);
    glCompileShader(secondFragmentShader);
    glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(secondFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //link the shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }    
    glDeleteShader(fragmentShader);

    //link the shader program
    unsigned int secondShaderProgram;
    secondShaderProgram = glCreateProgram();
    glAttachShader(secondShaderProgram, vertexShader);
    glAttachShader(secondShaderProgram, secondFragmentShader);
    glLinkProgram(secondShaderProgram);
    glGetShaderiv(secondShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(secondShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(secondFragmentShader);



    unsigned int VAO[2];
    unsigned int VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


	glm::mat4 transformMat = glm::mat4(	1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f, 
										0.0f, 0.0f, 1.0f, 0.0f, 
										0.0f, 0.0f, 0.0f, 1.0f) ;
	
	transformMat = glm::scale(transformMat, glm::vec3(0.5f, 1.0f, 0.0f));
	
		

    // render loop
    // swap buffers to render images
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		float currentTime = glfwGetTime();

        glUseProgram(shaderProgram);
		unsigned int f1transformLoc = glGetUniformLocation(secondShaderProgram, "transform");
		//transformMat = glm::rotate(transformMat, glm::radians(currentTime), glm::vec3(0.0f, 0.0f, 1.0f));
		//transformMat = glm::scale(transformMat, glm::vec3(sin(currentTime) * 10.0f, sin(currentTime) * 10.0f, 0.0f));
		glUniformMatrix4fv(f1transformLoc, 1, GL_FALSE, glm::value_ptr(transformMat));

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(secondShaderProgram);		

		unsigned int transformLoc = glGetUniformLocation(secondShaderProgram, "transform");
		//transformMat = glm::rotate(transformMat, glm::radians(currentTime), glm::vec3(0.0f, 0.0f, 1.0f));
		//transformMat = glm::scale(transformMat, glm::vec3(sin(currentTime) * 10.0f, sin(currentTime) * 10.0f, 0.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMat));

		glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);

    glfwTerminate();
    return 0;
}

// process key input
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //height of the rendering window
    glViewport(0, 0, width, height);
}