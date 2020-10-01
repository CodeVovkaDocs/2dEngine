#pragma once

enum class controllerType
{
	INPUT,
	AI
};

class Controller
{
public:

	virtual controllerType GetType() = 0;
	virtual ~Controller() {};
};

