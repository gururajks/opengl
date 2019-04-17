#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include "BaseShader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include<filesystem>
#include "Shader.h"
#include "Texture.h"
#include "Constants.h"
#include "Camera.h"
#include "CubeVertexBuffer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int SCR_WIDTH = 600;
int SCR_HEIGHT = 800;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
float yaw = -90.0f;	
float pitch = 0.0f;
float fov = 45.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(cameraPos, target, up);

bool firstMouse = true;

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
	
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


	unique_ptr<Shader> shader = make_unique<Shader>("..\\shaders\\vertexshader.glsl", "..\\shaders\\plainfragshader.glsl");
	unsigned int shaderProgram = shader->linkShader();

	unique_ptr<Shader> lampShader = make_unique<Shader>("..\\shaders\\vertexshader.glsl", "..\\shaders\\lampfragshader.glsl");
	unsigned int lampShaderProgram = lampShader->linkShader();
	
	glEnable(GL_DEPTH_TEST);
    

	unsigned int VAO[2];
	unsigned int VBO[2];
	CubeVertexBuffer cvb(VAO, VBO);

	unsigned int lampVAO[2];
	CubeVertexBuffer lampCvb(lampVAO, VBO);
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	//unsigned int lampVAO;
	//glGenVertexArrays(1, &lampVAO);
	//glBindVertexArray(lampVAO);

	//// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	glm::mat4 transformMat = glm::mat4(	1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f, 
										0.0f, 0.0f, 1.0f, 0.0f, 
										0.0f, 0.0f, 0.0f, 1.0f) ;
	
	transformMat = glm::scale(transformMat, glm::vec3(0.5f, 0.5f, 0.5f));
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	

    // render loop
    // swap buffers to render images
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
		

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		shader->setShaderUniform("transform", transformMat);
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 proj = glm::mat4(1);
		proj = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);		
		
		view = camera.viewMatrix();
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, up);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		shader->setShaderUniform("view", view);
		shader->setShaderUniform("proj", proj);
		
		model = glm::translate(model, lightPos);
		shader->setShaderUniform("model", model);
		shader->setShaderUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->setShaderUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setShaderUniform("lightPos", lightPos);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		
		glUseProgram(lampShaderProgram);
		lampShader->setShaderUniform("transform", transformMat);		
		lampShader->setShaderUniform("view", view);
		lampShader->setShaderUniform("proj", proj);
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.5f));
		lampShader->setShaderUniform("model", model);
		
		
		glBindVertexArray(VAO[0]);
		
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
			

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
	//glDeleteBuffers(2, EBO);
    glfwTerminate();
    return 0;
}

// process key input
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraFront * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraFront * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //height of the rendering window
    glViewport(0, 0, width, height);
}