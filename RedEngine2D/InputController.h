#pragma once
#include "Controller.h"
class InputController :
	public Controller
{
public:

	controllerType GetType(){ return controllerType::INPUT; }
};

