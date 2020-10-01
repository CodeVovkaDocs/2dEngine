#pragma once

#ifndef GAME_HEADER
#define GAME_HEADER 



#include "Graphics.h"
#include "Input.h"

#include "Level.h"
#include "ComponentList.h"
#include "GameInputData.h"
#include "InputRuleSet.h"
#include "MovementRuleSet.h"
#include "CursorRuleSet.h"
#include "FrameTimer.h"
#include "SystemDrawing.h"
#include "SystemCollision.h"

#include "CollisionEventHandler.h"
#include "EventSystem.h"

#include "TestLevel.h"
#include "SpriteDataScript.h"

#include <vector>



class Game
{
public:

	Game();
	~Game();

	void LinkGraphics(Graphics* graphics);

	void LinkInput(Input* input);

	void Start();

	void Update(double dt);

	void Draw();

	void End();


private:

	void AddSystem(System* system);
	void AddRuleSet(RuleSet* ruleSet);
	void InitSystems();
	void UpdateSystems();
	void ApplyRules();
	void UpdateGameInputData();

	Graphics* graph;
	Input* input;

	EventSystem* eventSystem;

	CollisionEventHandler* collisionHnd;

	inputData currentGameInputData;
	double currentDt;

	std::vector<RuleSet*> rules;
	std::vector<System*> systems;

	Level *currentLevelPtr;
};

#endif // !GAME_HEADER