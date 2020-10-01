#pragma once
#include "EntityComponent.h"
#include "GameMath.h"

class SpatialComponent :
	public EntityComponent
{
public:

	SpatialComponent() {};

	SpatialComponent(Shape* shape, Vec2 loc,bool collisionCheck) {
		this->shape = shape;
		this->location = loc;
		this->enableCollisionCheck = collisionCheck;
	};

	entityComponentType GetType() { return entityComponentType::SPATIAL; }

	void SetShape(Shape* shape) { this->shape = shape; }
	void SetLocation(Vec2 loc) { this->location = loc; }
	void SetCollisionCheck(bool check) { this->enableCollisionCheck = check; }

	Vec2 GetLocation() { return location; }
	Vec2 GetSize() { return shape->GetScale(); }
	Shape* GetShape() { return shape; }
	bool CollisionEnabled() { return enableCollisionCheck; }

private:

	Shape* shape;
	Vec2 location;
	bool enableCollisionCheck;

};

