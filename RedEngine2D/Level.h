#pragma once
#include "Entity.h"
#include "GameMath.h"
#include<vector>


class Level
{
public:

	Level(const char* name, int height, int width);
	~Level();

	int GetEntityVectorSize();
	int GetWidth();
	int GetHeight();

	void AddEntity(Entity *entity);
	void RemoveEntity(int entityId);
	void SetViewCenter(Vec2 center);

	Vec2 GetViewCenter();

	std::vector<Entity*>* GetEntityVector();

private:

	const char* name;
	int height;
	int width;

	Vec2 viewCenter;

	std::vector<Entity*> entityVector;

};

