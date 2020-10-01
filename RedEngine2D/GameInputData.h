#pragma once

enum class inputActionState
{
	START,
	END
};

struct inputData
{
	double cursorX;
	double cursorY;

	double cursorDeltaX;
	double cursorDeltaY;

	double cursorAbsPosX;
	double cursorAbsPosY;

	inputActionState action1;
	inputActionState action2;
};
