#pragma once
#include "RuleSet.h"
#include "GameInputData.h"
#include "GameMath.h"
#include <iostream>

class InputRuleSet :
	public RuleSet
{
public:

	InputRuleSet(inputData* gameInput);

	void Apply(Entity* entity);

private:

	inputData* input;
};

