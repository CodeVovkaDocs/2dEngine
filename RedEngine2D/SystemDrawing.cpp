#include "SystemDrawing.h"



void SystemDrawing::Init(Level* level)
{

}

void SystemDrawing::Update(Level* level, double dt)
{
	currentLevel = level;
	std::vector<Entity*> *gameEntityVector = level->GetEntityVector();

	for (auto itr = gameEntityVector->begin(); itr != gameEntityVector->end(); ++itr)
	{
		if ((*itr)->CheckForComponents({ entityComponentType::DRAW }))
		{
			UpdateEntitySpriteData(*itr);
		}
	}
}


void SystemDrawing::AddDrawData(const char* entName, entityState state, drawData data)
{
	std::pair<const char*, entityState> key(entName, state);
	drawDataDict[key] = data;
}

void SystemDrawing::UpdateEntitySpriteData(Entity* ent)
{
	std::pair<const char*, entityState> key(ent->GetName(), ent->GetState());

	if (drawDataDict.find(key) != drawDataDict.end())
	{
		DrawComponent* draw = ent->GetComponentPtr<DrawComponent>(entityComponentType::DRAW);
		spriteData spriteData = draw->GetSpriteData();
	
		drawData drawInfo = drawDataDict[key];

		spriteData.tex = drawInfo.tex;
		spriteData.frameSize = drawInfo.frameSize;
		spriteData.scale = drawInfo.size;
		spriteData.color = drawInfo.color;
		spriteData.depth = drawInfo.depth;
		spriteData.background = drawInfo.background;
		spriteData.angle = drawInfo.angle;
		spriteData.flipX = drawInfo.flipX;
		spriteData.flipY = drawInfo.flipY;
		spriteData.frame = cycleAnimation(drawInfo.startFrame, drawInfo.endFrame, drawInfo.frameTime, draw);

		if (ent->CheckForComponents({ entityComponentType::SPATIAL }))
		{
			SpatialComponent* cmpPtr = ent->GetComponentPtr<SpatialComponent>(entityComponentType::SPATIAL);

			double locationX = cmpPtr->GetLocation().x;
			double locationY = cmpPtr->GetLocation().y;
			double sizeX = cmpPtr->GetSize().x;
			double sizeY = cmpPtr->GetSize().y;

			Vec2 centeredLoc(locationX , locationY );
			spriteData.loc = Vec2(centeredLoc.x + drawInfo.offset.x, centeredLoc.y + drawInfo.offset.y);

			if (ent->GetName() == "FIGHTER")
			{
				currentLevel->SetViewCenter(spriteData.loc);
			}

			spriteData.collisionBoxLoc = cmpPtr->GetLocation();
			spriteData.collisionBoxSize = cmpPtr->GetSize();

		}

		if (ent->CheckForComponents({ entityComponentType::MOVEMENT }) && drawInfo.flipInMovementDirection)
		{
			MovementComponent* movePtr = ent->GetComponentPtr<MovementComponent>(entityComponentType::MOVEMENT);

			double direction = movePtr->GetDirection();
			if (direction >= 90.0f && direction <= 270.0f)
			{
				spriteData.flipX = false;
			}
			else
			{
				spriteData.flipX = true;
			}
		}

		draw->SetSpriteData(spriteData);
		
	}

}

int SystemDrawing::cycleAnimation(int startFrame, int endFrame, double frameTime, DrawComponent* draw)
{
	draw->SetFrameTime(draw->GetFrameTime() + (*currentDt));
	int currentFrame = draw->GetDrawFrame();

	if (draw->GetFrameTime() >= frameTime)
	{
		if (currentFrame >= startFrame && currentFrame < endFrame)
		{
			draw->SetFrameTime(0.0f);
			++currentFrame;
		}
		else
		{
			draw->SetFrameTime(0.0f);
			currentFrame = startFrame;
		}		
	}

	return currentFrame;
}
