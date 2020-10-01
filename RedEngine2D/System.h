#pragma once
#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER


#include "Level.h"
#include "Entity.h"
#include "ComponentList.h"
#include <vector>

class System
{
public:

	virtual void Init(Level *level) = 0;

	virtual void Update(Level* level, double dt) = 0;

	virtual ~System() {};
};

#endif 

