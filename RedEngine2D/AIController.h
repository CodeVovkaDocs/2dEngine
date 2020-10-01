#pragma once
#include "Controller.h"
class AIController :
	public Controller
{
public:

	controllerType GetType() { return controllerType::AI; };
};

