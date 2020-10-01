#include "Game.h"

Game::Game()
{
	currentLevelPtr = nullptr;
}

Game::~Game(){}


void Game::LinkGraphics(Graphics* graphics)
{
	graph = graphics;
}

void Game::LinkInput(Input* input)
{
	this->input = input;
}


void Game::Start()
{

	currentLevelPtr = CreateLevel();

	eventSystem = new EventSystem();

	collisionHnd = new CollisionEventHandler();


	
	eventSystem->AddEventHandler("COLLISION_EVENT", collisionHnd, &CollisionEventHandler::collisionEventNotice);
	
	SystemDrawing* drawSystem = new SystemDrawing(&currentDt);
	GetData(drawSystem);
	AddSystem(drawSystem);

	SystemCollision* systemCollision = new SystemCollision();
	systemCollision->LinkEventSystem(eventSystem);
	AddSystem(systemCollision);

	AddRuleSet(new InputRuleSet(&currentGameInputData));
	AddRuleSet(new MovementRuleSet(&currentDt));
	AddRuleSet(new CursorRuleSet(&currentGameInputData));

	InitSystems();
}

void Game::InitSystems()
{
	for (auto itr = systems.begin(); itr != systems.end(); ++itr)
	{
		(*itr)->Init(currentLevelPtr);
	}
}

void Game::UpdateSystems()
{
	for (auto itr = systems.begin(); itr != systems.end(); ++itr)
	{
		(*itr)->Update(currentLevelPtr,currentDt);
	}
}

void Game::Update(double dt)
{
	currentDt = dt;
	UpdateGameInputData();
	UpdateSystems();
	ApplyRules();
	eventSystem->HandleEvents();
}



void Game::AddSystem(System* system)
{
	systems.push_back(system);
}

void Game::AddRuleSet(RuleSet* ruleSet)
{
	rules.push_back(ruleSet);
}


void Game::ApplyRules()
{
	std::vector<Entity*>* currentEntVec = currentLevelPtr->GetEntityVector();

	for (auto entItr = currentEntVec->begin(); entItr != currentEntVec->end(); ++entItr)
	{
		for (auto ruleItr = rules.begin(); ruleItr != rules.end(); ++ruleItr)
		{
			(*ruleItr)->Apply(*entItr);
		}
	}

}

void Game::UpdateGameInputData()
{
	double newMouseX = input->GetMouseX();
	double newMouseY = input->GetMouseY();

	Vec2 levelPos = currentLevelPtr->GetViewCenter();
	double viewWidth = graph->GetWindowWidth();
	double viewHeight = graph->GetWindowHeight();

	currentGameInputData.cursorDeltaX = newMouseX - currentGameInputData.cursorX;
	currentGameInputData.cursorDeltaY = newMouseY - currentGameInputData.cursorY;

	currentGameInputData.cursorAbsPosX = ((levelPos.x - viewWidth / 2) + newMouseX);
	currentGameInputData.cursorAbsPosY = ((levelPos.y - viewHeight / 2) + newMouseY);

	currentGameInputData.cursorX = newMouseX;
	currentGameInputData.cursorY = newMouseY;

	if (input->GetLeftMouseButtonState() == buttonState::PRESS)
	{
		currentGameInputData.action1 = inputActionState::START;
	}

	if (input->GetLeftMouseButtonState() == buttonState::RELEASE)
	{
		currentGameInputData.action1 = inputActionState::END;
	}

	if (input->GetRightMouseButtonState() == buttonState::PRESS)
	{
		currentGameInputData.action2 = inputActionState::START;
	}

	if (input->GetRightMouseButtonState() == buttonState::RELEASE)
	{
		currentGameInputData.action2 = inputActionState::END;
	}

}

///FIX SIZE!
void Game::Draw()
{
	spriteData* drawData = new spriteData[currentLevelPtr->GetEntityVector()->size()];
	int n = 0;

	for (auto itr = currentLevelPtr->GetEntityVector()->begin(); itr != currentLevelPtr->GetEntityVector()->end(); ++itr)
	{
		if ((*itr)->CheckForComponents({ entityComponentType::DRAW }))
		{
			DrawComponent* draw = (*itr)->GetComponentPtr<DrawComponent>(entityComponentType::DRAW);
			drawData[n] = draw->GetSpriteData();
			n++;
		}
	}

	graph->Draw(drawData, currentLevelPtr->GetEntityVector()->size(), currentLevelPtr->GetViewCenter().x, currentLevelPtr->GetViewCenter().y);
	delete[] drawData;
}


void Game::End(){}
