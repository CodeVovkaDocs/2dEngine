#pragma once
#include "EntityComponent.h"
#include "SpriteData.h"
#include <utility>
#include <map>





class DrawComponent :
	public EntityComponent
{
public:

	DrawComponent() { currentFrameTime = 0.0f; }

	entityComponentType GetType() { return entityComponentType::DRAW; }

	void SetSpriteData(spriteData data) { currentSpriteData = data; }

	spriteData GetSpriteData() {return currentSpriteData;}

	int GetDrawFrame() { return currentSpriteData.frame; }

	double GetFrameTime() { return currentFrameTime; }

	void SetFrameTime(double time) { currentFrameTime = time; }



private:

	spriteData currentSpriteData;
	double currentFrameTime;

};

