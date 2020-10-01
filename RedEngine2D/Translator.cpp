#include "Translator.h"


Translator::Translator()
{
	currentInputData.action1 == inputActionState::END;
	currentInputData.action2 == inputActionState::END;
	currentInputData.cursorX == 0.0f;
	currentInputData.cursorY == 0.0f;
}

void Translator::Init(Input* input)
{
	currentInputData.cursorAbsPosX = 0.0f;
	currentInputData.cursorAbsPosY = 0.0f;
}

Translator::~Translator()
{

}


void Translator::UpdateInputData(Input* input)
{
	double newMouseX = input->GetMouseX();
	double newMouseY = input->GetMouseY();

	currentInputData.cursorDeltaX = newMouseX - currentInputData.cursorX;
	currentInputData.cursorDeltaY = newMouseY - currentInputData.cursorY;

	currentInputData.cursorAbsPosX += currentInputData.cursorDeltaX;
	currentInputData.cursorAbsPosY += currentInputData.cursorDeltaY;

	currentInputData.cursorX = newMouseX;
	currentInputData.cursorY = newMouseY;

	if (input->GetLeftMouseButtonState() == buttonState::PRESS)
	{
		currentInputData.action1 = inputActionState::START;
	}

	if (input->GetLeftMouseButtonState() == buttonState::RELEASE)
	{
		currentInputData.action1 = inputActionState::END;
	}

	if (input->GetRightMouseButtonState() == buttonState::PRESS)
	{
		currentInputData.action2= inputActionState::START;
	}

	if (input->GetRightMouseButtonState() == buttonState::RELEASE)
	{
		currentInputData.action2 = inputActionState::END;
	}


}


inputData* Translator::GetCurrentInputData()
{
	return &currentInputData;
}