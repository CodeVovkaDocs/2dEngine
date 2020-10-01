#pragma once
#include "EntityComponent.h"
class MovementComponent :
	public EntityComponent
{
public:

	MovementComponent()
	{
		maxSpeed = 0.0f;
		currentSpeed = 0.0f;
		currentDirection = 0.0f;
	}
	MovementComponent(double speed, double direction, double limit)
	{
		maxSpeed = limit;
		currentDirection = direction;
		currentSpeed = speed;
	}

	entityComponentType GetType() { return entityComponentType::MOVEMENT; }

	void SetSpeed(double speed){currentSpeed = speed;}
	void SetDirection(double direction){currentDirection = direction;}
	void SetMaxSpeed(double limit){maxSpeed = limit;}

	double GetSpeed(){return currentSpeed;}
	double GetDirection(){return currentDirection;}
	double GetMaxSpeed(){return maxSpeed;}

private:

	double maxSpeed;
	double currentSpeed;
	double currentDirection;
};

