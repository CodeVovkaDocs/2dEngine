#pragma once

#include "Entity.h"
#include "ComponentList.h"

class RuleSet
{
public:

	virtual void Apply(Entity* entity) = 0;

	virtual ~RuleSet() {};
};

