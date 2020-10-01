#include "SystemCollision.h"


void SystemCollision::Init(Level* level){}

void SystemCollision::LinkEventSystem(EventSystem* system){this->eventSystem = system;}

void SystemCollision::Update(Level* level, double dt)
{
	std::vector<Entity*>* gameEntityVector = level->GetEntityVector();

	for (auto itr = gameEntityVector->begin(); itr != gameEntityVector->end(); ++itr)
	{
		if ((*itr)->CheckForComponents({ entityComponentType::SPATIAL }))
		{
			CheckEntityCollision((*itr), gameEntityVector);
		}
	}
}


void SystemCollision::CheckEntityCollision(Entity* ent, std::vector<Entity*>* entVec)
{

	for (auto itr = entVec->begin(); itr != entVec->end(); ++itr)
	{
		if ((*itr)->CheckForComponents({ entityComponentType::SPATIAL }) && (*itr)->GetEntityId() != ent->GetEntityId())
		{

			if (CheckForCollision(ent, (*itr)))
			{
				eventSystem->AddEvent<CollisionEvent,Entity*,Entity*>(ent, (*itr));
			}

		}
	}

}

bool SystemCollision::CheckForCollision(Entity* ent1, Entity* ent2)
{
	SpatialComponent* spt1 = ent1->GetComponentPtr<SpatialComponent>(entityComponentType::SPATIAL);
	SpatialComponent* spt2 = ent2->GetComponentPtr<SpatialComponent>(entityComponentType::SPATIAL);

	if (!(spt1->CollisionEnabled() && spt2->CollisionEnabled()))
	{
		return false;
	}

	bool isCollision = false;

	Vec2 loc1 = spt1->GetLocation();
	Vec2 loc2 = spt2->GetLocation();

	Shape* shape1 = spt1->GetShape();
	Shape* shape2 = spt2->GetShape();

	ShapeType type1 = shape1->GetShapeType();
	ShapeType type2 = shape2->GetShapeType();

	if (type1 == ShapeType::QUAD && type2 == ShapeType::QUAD)
	{
		Quad* quad1 = static_cast<Quad*>(shape1);
		Quad* quad2 = static_cast<Quad*>(shape2);

		if ((loc1.x >= loc2.x && loc1.x <= (loc2.x + quad2->size.x)) || (loc1.x <= loc2.x && loc2.x <= (loc1.x + quad1->size.x)))
		{
			if ((loc1.y >= loc2.y && loc1.y <= (loc2.y + quad2->size.y)) || (loc1.y <= loc2.y && loc2.y <= (loc1.y + quad1->size.y)))
			{
				isCollision = true;
			}
		}
	}

	return isCollision;
}