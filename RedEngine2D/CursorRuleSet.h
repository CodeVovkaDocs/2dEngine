#pragma once
#include "RuleSet.h"
#include "GameInputData.h"
#include <iostream>

class CursorRuleSet :
	public RuleSet
{
public:

	CursorRuleSet(inputData* input);
	void Apply(Entity* entity);

private:

	inputData* input;
};

