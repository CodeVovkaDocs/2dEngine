#include "Level.h"


Level::Level(const char* name, int height, int width)
{
	this->name = name;
	this->height = height;
	this->width = width;
	viewCenter = Vec2(0.0f, 0.0f);
}

Level::~Level(){}

void Level::AddEntity(Entity *entity)
{
	entityVector.push_back(entity);
}

void Level::RemoveEntity(int entityId)
{

	for (int i = 0; i < (int)entityVector.size(); i++)
	{
		if (entityVector[i]->GetEntityId() == entityId)
		{
			delete(&entityVector[i]);
			entityVector.erase(entityVector.begin()+i);
		}
	}

}

int Level::GetEntityVectorSize()
{
	return entityVector.size();
}

std::vector<Entity*>* Level::GetEntityVector()
{
	return &entityVector;
}

int Level::GetWidth()
{
	return width;
}

int Level::GetHeight()
{
	return height;
}

void Level::SetViewCenter(Vec2 view)
{
	viewCenter = view;
	if (viewCenter.x > width)
	{
		viewCenter.x = width;
	}
	if (viewCenter.x < 0)
	{
		viewCenter.x = 0;
	}
	if (viewCenter.y > height)
	{
		viewCenter.y = height;
	}
	if (viewCenter.y < 0)
	{
		viewCenter.y = 0;
	}
}

Vec2 Level::GetViewCenter()
{
	return viewCenter;
}

