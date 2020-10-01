#pragma once


#include "Game.h"
#include "Graphics.h"
#include "Loader.h"
#include "Input.h"
#include <iostream>

class Translator
{
public:

	Translator();
	~Translator();

	void Init(Input* input);

	void UpdateInputData(Input *input);

	inputData* GetCurrentInputData();

private:

	inputData currentInputData;

};



