#pragma once
#include <GLFW/glfw3.h>

enum class buttonState
{
	PRESS,
	RELEASE
};

class Input
{
public:

	Input();

	~Input();

	void SetWindowRef(GLFWwindow* window);

	double GetMouseX();

	double GetMouseY();

	buttonState GetLeftMouseButtonState();

	buttonState GetRightMouseButtonState();

private:

	GLFWwindow* windowPtr;

	static void CursorCallback(GLFWwindow* window, double xpos, double ypos);

	static void MouseButtonCallback(GLFWwindow* window, int buton, int action, int mods);

	static double mouse_x, mouse_y;

	static buttonState mouseLeft, mouseRight;

};

