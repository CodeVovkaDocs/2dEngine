#include "MainWindow.h"

MainWindow::MainWindow()
{
	this->width = 800;
	this->height = 600;
	this->glfwWindow = nullptr;
	this->bufferHeight = 0;
	this->bufferWidth = 0;
}

MainWindow::MainWindow(GLint width, GLint heigh)
{
	this->width = width;
	this->height = heigh;
	this->glfwWindow = nullptr;
	this->bufferHeight = 0;
	this->bufferWidth = 0;
}

int MainWindow::init()
{
	if(!glfwInit())
	{
		printf("Error: failed to init glfw");
		glfwTerminate();
		return 1;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

	glfwWindow = glfwCreateWindow(width, height, "REngine", NULL, NULL);

	if (!glfwWindow)
	{
		printf("Error: failed to create window");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(glfwWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(glfwWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Error: failed to init glew");
		glfwDestroyWindow(glfwWindow);
		glfwTerminate();
		return 1;
	}

	glfwSetWindowAttrib(glfwWindow, GLFW_RESIZABLE, GLFW_FALSE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, width, height);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//glfwSetInputMode(glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	return 0;
}



void MainWindow::SwapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}


void MainWindow::PollEvents()
{
	glfwPollEvents();
}


bool MainWindow::GetShouldClose()
{
	return glfwWindowShouldClose(glfwWindow);
}


GLFWwindow* MainWindow::GetWindowPtr()
{
	return this->glfwWindow;
}

GLfloat MainWindow::GetBufferWidth()
{
	return this->bufferWidth;
}


GLfloat MainWindow::GetBufferHeight()
{
	return this->bufferHeight;
}





MainWindow::~MainWindow()
{
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}


