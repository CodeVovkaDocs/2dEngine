#pragma once
#include "Event.h"
#include "Entity.h"
#include <iostream>
class CollisionEvent : public Event
{
public:

	const char* GetId() { return "COLLISION_EVENT"; }

	~CollisionEvent() { 

		//std::cout << "Erased" << "\n";
	}

	CollisionEvent(Entity* ent1, Entity* ent2)
	{
		this->ent1 = ent1;
		this->ent2 = ent2;
	}

	Entity* ent1;
	Entity*	ent2;
};
