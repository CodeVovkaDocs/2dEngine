#pragma once
#include "RuleSet.h"
#include "GameMath.h"


class MovementRuleSet :
	public RuleSet
{
public:

	MovementRuleSet(double* dtPtr);

	void Apply(Entity* entity);

private:

	double* currentDt;
};

