#include "MovementRuleSet.h"


MovementRuleSet::MovementRuleSet(double* dtPtr)
{
	currentDt = dtPtr;
}

void MovementRuleSet::Apply(Entity* entity)
{
	if (entity->CheckForComponents({entityComponentType::SPATIAL,entityComponentType::MOVEMENT}))
	{

		MovementComponent* movePtr = entity->GetComponentPtr<MovementComponent>(entityComponentType::MOVEMENT);
		SpatialComponent* sptPtr = entity->GetComponentPtr<SpatialComponent>(entityComponentType::SPATIAL);



		if (movePtr->GetSpeed() > 0.0f)
		{
			float pi = 3.141592;
			double currentX = sptPtr->GetLocation().x;
			double currentY = sptPtr->GetLocation().y;
			double speed = movePtr->GetSpeed() * (*currentDt);

			double radDir = movePtr->GetDirection() * pi / 180.0f;			

			double dX = speed * cos(radDir);
			double dY = speed * sin(radDir);

			sptPtr->SetLocation(Vec2(currentX + dX, currentY + dY));

			entity->SetState(entityState::MOVING);
		}
		else
		{
			entity->SetState(entityState::IDLE);
		}
		
	}
}
