#pragma once
#include "CollisionEvent.h"
#include <iostream>

class CollisionEventHandler
{
public:

	void collisionEventNotice(Event* event)
	{
		CollisionEvent* collison = static_cast<CollisionEvent*>(event);
		std::cout << "Collision event info:" << collison->ent1->GetName() << " :: " << collison->ent2->GetName() << "\n";
	}

};

