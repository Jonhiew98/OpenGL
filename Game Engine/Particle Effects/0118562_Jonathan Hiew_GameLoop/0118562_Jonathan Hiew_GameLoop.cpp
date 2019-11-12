// 0118562_Jonathan Hiew_GameLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include "Application.h"

void gameUpdate(float fps, float deltaTime)
{
	std::cout <<"Fps: "<< fps <<" delta time : " << deltaTime << std::endl;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glViewport(0, 0, 1080, 720);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0,1080,0,720);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float currentTime = 0;
	float lastTime = glfwGetTime();

	Application app;
	app.Start();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//delta time
		currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		app.Update(deltaTime);
		app.Draw();
	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
