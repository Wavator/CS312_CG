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
				else if (color < -1.0f)
				{
					color = 1.0 - (-1.0f - color);
				}
				ver_col[i * 2 + j + 3] = color;
			}
		}
	}
}

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"uniform mat4 transform;\n"
"out vec3 outcolor;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	outcolor = aColor;"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 outcolor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(outcolor, 1.0f);\n"
"}\n\0";


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
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1);
		/*draw a triangle*/
		glUseProgram(shaderProgram);
		glm::mat4 transform1 = glm::mat4(1.0f);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		debug("%f, %f\n", xpos, ypos);
		(xpos -= windowL / 2) /= windowL;
		(ypos -= windowD / 2) /= windowD;
		transform1 = glm::translate(transform1, glm::vec3((float)xpos, -(float)ypos, 0.0f));
		transform1 = glm::rotate(transform1, 3 * (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 3);
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
