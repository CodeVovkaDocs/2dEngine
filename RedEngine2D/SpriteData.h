#pragma once

#ifndef SPRITE_DATA
#define SPRITE_DATA

#include "Texture.h"
#include "GameMath.h"

struct spriteData
{
	Texture* tex;
	float frameSize;
	Vec2 loc;
	Vec2 scale;
	float angle;
	bool flipX;
	bool flipY;
	Vec3 color;
	float depth;
	int frame = 0.0f;
	bool background = false;

	//Collison Box Draw data
	Vec2 collisionBoxLoc = Vec2(0.0f, 0.0f);
	Vec2 collisionBoxSize = Vec2(32.0f, 32.0f);
};



#endif // !SPRITE_DATA

