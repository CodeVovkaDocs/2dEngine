#include "Input.h"

double Input::mouse_x;
double Input::mouse_y;
buttonState Input::mouseLeft;
buttonState Input::mouseRight;

Input::Input()
{
	windowPtr = nullptr;
	mouse_x = 0.0f;
	mouse_y = 0.0f;
	mouseLeft = buttonState::RELEASE;
	mouseRight = buttonState::RELEASE;
}

Input::~Input()
{

}

void Input::SetWindowRef(GLFWwindow* window)
{
	this->windowPtr = window;
	glfwSetCursorPosCallback(windowPtr, Input::CursorCallback);
	glfwSetMouseButtonCallback(windowPtr, Input::MouseButtonCallback);
}

void Input::CursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	Input::mouse_x = xpos;
	Input::mouse_y = ypos;
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			Input::mouseLeft = buttonState::PRESS;
		}
		else
		{
			if (action == GLFW_RELEASE)
			{
				Input::mouseLeft = buttonState::RELEASE;
			}
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			Input::mouseRight = buttonState::PRESS;
		}
		else
		{
			if (action == GLFW_RELEASE)
			{
				Input::mouseRight = buttonState::RELEASE;
			}
		}
	}
}

double Input::GetMouseX()
{
	return mouse_x;
}

double Input::GetMouseY()
{
	return mouse_y;
}

buttonState Input::GetLeftMouseButtonState()
{
	return mouseLeft;
}

buttonState Input::GetRightMouseButtonState()
{
	return mouseRight;
}