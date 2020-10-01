#include "CursorRuleSet.h"

CursorRuleSet::CursorRuleSet(inputData* input)
{
	this->input = input;
}

void CursorRuleSet::Apply(Entity* entity)
{
	if (entity->GetName() == "CURSOR")
	{
		SpatialComponent* sptPtr = entity->GetComponentPtr<SpatialComponent>(entityComponentType::SPATIAL);
		sptPtr->SetLocation(Vec2(input->cursorAbsPosX, input->cursorAbsPosY));
	}
}
