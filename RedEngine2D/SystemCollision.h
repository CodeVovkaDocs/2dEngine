#pragma once
#include "System.h"
#include <vector>
#include <iostream>
#include "EventSystem.h"

class SystemCollision :
	public System
{
public:

	void Init(Level* level);

	void Update(Level* level, double dt);

	void LinkEventSystem(EventSystem* system);

private:

	EventSystem* eventSystem;

	bool CheckForCollision(Entity* ent1, Entity* ent2);
	void CheckEntityCollision(Entity* ent, std::vector<Entity*>* entVec);

};

