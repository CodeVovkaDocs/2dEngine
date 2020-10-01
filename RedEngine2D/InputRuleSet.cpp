#include "InputRuleSet.h"


InputRuleSet::InputRuleSet(inputData* gameInput)
{
	input = gameInput;
}


void InputRuleSet::Apply(Entity* entity)
{

	if (entity->CheckForComponents({ entityComponentType::CONTROL,entityComponentType::SPATIAL,entityComponentType::MOVEMENT }))
	{
		ControlComponent* ctrlPtr = entity->GetComponentPtr<ControlComponent>(entityComponentType::CONTROL);
		MovementComponent* movePtr = entity->GetComponentPtr<MovementComponent>(entityComponentType::MOVEMENT);
		SpatialComponent* sptPtr = entity->GetComponentPtr<SpatialComponent>(entityComponentType::SPATIAL);


		if (ctrlPtr->GetController()->GetType() == controllerType::INPUT)
		{

			double angle = vectorAngleDeg(sptPtr->GetLocation().x, input->cursorAbsPosX, sptPtr->GetLocation().y, input->cursorAbsPosY);

			double boxTop = sptPtr->GetLocation().y ;
			double boxBottom = sptPtr->GetLocation().y + sptPtr->GetSize().y;
			double boxLeft = sptPtr->GetLocation().x ;
			double boxRight = sptPtr->GetLocation().x + sptPtr->GetSize().x ;

			

			if (input->action1 == inputActionState::START)
			{
				if ((input->cursorAbsPosX >= boxRight || input->cursorAbsPosX <= boxLeft) || (input->cursorAbsPosY >= boxBottom || input->cursorAbsPosY <= boxTop))
				{
					movePtr->SetSpeed(movePtr->GetMaxSpeed());
					movePtr->SetDirection(angle);
				}
				else
				{
					movePtr->SetSpeed(0.0f);
				}
			}

			if (input->action1 == inputActionState::END)
			{
				movePtr->SetSpeed(0.0f);
			}

		}
	}

}