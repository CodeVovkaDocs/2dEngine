#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Input.h"

class MainWindow
{
public:

	MainWindow();
	MainWindow(GLint width,GLint heigh);

	int init();

	void SwapBuffers();
	void PollEvents();
	bool GetShouldClose();

	GLFWwindow* GetWindowPtr();
	GLfloat GetBufferWidth();
	GLfloat GetBufferHeight();




	~MainWindow();

private:


	GLFWwindow* glfwWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;


};

