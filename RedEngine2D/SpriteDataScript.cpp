#include "SpriteDataScript.h"

void GetData(SystemDrawing* system)
{
	Texture* cursorTex = Loader::GetTexture("cursor");
	Texture* fighterTex = Loader::GetTexture("player");
	Texture* skyTex = Loader::GetTexture("sky");
	Texture* wallTex = Loader::GetTexture("wall");

	drawData cursorData;
	cursorData.tex = cursorTex;
	cursorData.frameSize = 16.0f;
	cursorData.size = Vec2(32.0f,32.0f);
	cursorData.offset = Vec2(-8.0f, -8.0f);
	cursorData.depth = 0.8f;

	drawData wallData;
	wallData.tex = wallTex;
	wallData.frameSize = 32.0f;
	wallData.size = Vec2(64.0f, 64.0f);
	wallData.depth = 0.5f;

	drawData fighterDataIDLE;
	fighterDataIDLE.tex = fighterTex;
	fighterDataIDLE.frameSize = 32.0f;
	fighterDataIDLE.size = Vec2(64.0f, 64.0f);
	fighterDataIDLE.depth = 0.6f;
	fighterDataIDLE.flipInMovementDirection = true;
	fighterDataIDLE.offset = Vec2(-16.0f, -32.0f);

	drawData fighterDataMOVING;
	fighterDataMOVING.tex = fighterTex;
	fighterDataMOVING.frameSize = 32.0f;
	fighterDataMOVING.size = Vec2(64.0f, 64.0f);
	fighterDataMOVING.depth = 0.6f;
	fighterDataMOVING.startFrame = 6;
	fighterDataMOVING.endFrame = 11;
	fighterDataMOVING.frameTime = 0.06f;
	fighterDataMOVING.flipInMovementDirection = true;
	fighterDataMOVING.offset = Vec2(-16.0f, -32.0f);

	drawData skyData;
	skyData.tex = skyTex;
	skyData.frameSize = 1056.0f;
	skyData.size = Vec2(2000.0f, 2000.0f);
	skyData.depth = 0.0f;

	system->AddDrawData("CURSOR", entityState::IDLE, cursorData);
	system->AddDrawData("WALL", entityState::IDLE, wallData);
	system->AddDrawData("SKY", entityState::IDLE, skyData);
	system->AddDrawData("FIGHTER", entityState::IDLE, fighterDataIDLE);
	system->AddDrawData("FIGHTER", entityState::MOVING, fighterDataMOVING);
}