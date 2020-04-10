/*
Author: Wavator
*/
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifdef Local
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) 
#endif
using namespace std;

GLFWwindow* window;
const int windowL = 640, windowD = 480;
typedef GLuint vao;
typedef GLuint vbo;
typedef GLuint shader;
typedef GLuint GLpro;
const float vertex[] = { 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f,  0.5f, 0.0f, -0.5f,
		0.5f, 0.0f, 0.0f, 0.75f, 0.0f, 0.75f,  0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 0.75f, 0.75f,
		0.0f, 0.5f,  0.5f, 0.0f, 0.0f, 0.75f, 0.0f };
float ver_col[60];

void gen_color()
{
	for (int i = 0; i < 30; ++i)
	{
		if (i % 3 == 0)
		{
			for (int j = 0; j < 3; ++j)
			{
				ver_col[i * 2 + j] = vertex[i + j];
				float color = vertex[i + j] + 0.5;
				if (color > 1.0f)
				{
					color = -1.0f + (color - 1.0f);
				}
				ver_col[i * 2 + j + 3] = color;
			}
		}
	}
}
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 outcolor;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	outcolor = aColor;"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 outcolor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(outcolor, 1.0f);\n"
"}\n\0";
namespace camera {
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;
	GLfloat lastX = windowD / 2.0;
	GLfloat lastY = windowL / 2.0;
	GLfloat deltaTime, lastFrame;
	GLfloat radioWindow = (GLfloat)windowL / (GLfloat)windowD;

	//WASD
	void processInput(GLFWwindow *window)
	{

		float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPos += cameraSpeed * cameraFront;
			cerr << 'w' << endl;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPos -= cameraSpeed * cameraFront;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
	}
	//mouse
	bool firstMouse = true;
	void mouse_opt(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
		lastX = xpos;
		lastY = ypos;

		GLfloat sensitivity = 0.05;	// Change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
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
}
int main()
{
	gen_color();
	debug("color\n");
	for (int i = 0; i < 60; ++i)
	{
		debug("%f ", ver_col[i]);
		if ((i + 1) % 6 == 0)
		{
			debug("\n");
		}
	}
	/*pre check glfw and glad init.*/
	if (!glfwInit())
	{
		debug("GLFW init failed.");
		return -1;
	}
	window = glfwCreateWindow(windowL, windowD, "11612908_zhaoyu", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		debug("window init failed.");
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		debug("Load glad failed");
		return -1;
	}
	glfwSetCursorPosCallback(window, camera::mouse_opt);
	vao VAO;
	vbo VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	debug("VAO = %u, VBO = %u\n", VAO, VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	debug("VAO = %u, VBO = %u\n", VAO, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ver_col), ver_col, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	shader vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	shader fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLpro shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	/*core code*/

	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		camera::deltaTime = currentFrame - camera::lastFrame;
		camera::lastFrame = currentFrame;

		glfwPollEvents();
		camera::processInput(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glm::mat4 view;
		view = glm::lookAt(camera::cameraPos, camera::cameraPos + camera::cameraFront, camera::cameraUp);
		// Projection 
		glm::mat4 projection;
		projection = glm::perspective(45.0f, camera::radioWindow, 0.1f, 100.0f);
		// Get the uniform locations
		GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(VAO);
		for (int i = 0; i < 8; ++i)
		{
			if (i != 3 && i != 4) glDrawArrays(GL_TRIANGLES, i, 3);
		}
		glBindVertexArray(0);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	/*close window*/
	glfwTerminate();
	return 0;
}
