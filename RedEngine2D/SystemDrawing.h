#pragma once
#include "System.h"
#include "Loader.h"
#include <iostream>
#include <utility>
#include <map>


struct drawData
{
	//Texture data
	Texture* tex = nullptr;
	float frameSize = 32.0f;
	//Position data
	Vec2 offset = Vec2(0.0f,0.0f);
	Vec2 size = Vec2(32.0f,32.0f);
	//Angle data
	float angle = 0.0f;
	bool flipX = false;
	bool flipY = false;
	bool flipInMovementDirection = false;
	//Color&Depth data
	Vec3 color = Vec3(1.0f,1.0f,1.0f);
	float depth = 0.0f;
	bool background = false;
	//Animation data
	int startFrame = 0;
	int endFrame = 0;
	double frameTime = 0.0f;

	
};

class SystemDrawing :
	public System
{
public:

	SystemDrawing(double* dtPtr) { currentDt = dtPtr; currentLevel = nullptr; }
	~SystemDrawing() {}

	void AddDrawData(const char* entName, entityState state, drawData data);

	void Init(Level* level);
	void Update(Level* level, double dt);

private:

	std::map<std::pair<const char*, entityState>, drawData> drawDataDict;

	void UpdateEntitySpriteData(Entity* ent);
	int cycleAnimation(int startFrame, int endFrame, double frameTime, DrawComponent *draw);

	Level* currentLevel;
	double* currentDt;
};

