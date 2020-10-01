#pragma once
#include "EntityComponent.h"
#include "Controller.h"

class ControlComponent :
	public EntityComponent
{
public:

	ControlComponent(){myController = nullptr;}

	ControlComponent(Controller *controller){myController = controller;}

	entityComponentType GetType(){return entityComponentType::CONTROL;}

	Controller* GetController(){return myController;}

	void SetController(Controller *controller){myController = controller;}

private:

	Controller* myController;

};

