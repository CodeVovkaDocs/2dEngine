#include "TestLevel.h"

Level* CreateLevel()
{
	const char* levelName = "TEST LEVEL 01";
	int levelWidth = 2000;
	int levelHeight = 2000;

	Level* lvl = new Level(levelName, levelHeight, levelWidth);

	Entity* cursor = new Entity("CURSOR", entityState::IDLE);
	cursor->AddComponent(new SpatialComponent(new Quad(Vec2(16.0f, 16.0f)),Vec2(0.0f,0.0f), true));
	cursor->AddComponent(new DrawComponent());

	Entity* player = new Entity("FIGHTER", entityState::IDLE);
	player->AddComponent(new SpatialComponent(new Quad(Vec2(32.0f, 32.0f)), Vec2(400.0f, 400.0f),true));
	player->AddComponent(new MovementComponent(0.0f, 0.0f, 150.0f));
	player->AddComponent(new ControlComponent(new InputController()));
	player->AddComponent(new DrawComponent());


	Entity* wall1 = new Entity("WALL", entityState::IDLE);
	wall1->AddComponent(new SpatialComponent(new Quad(Vec2(64.0f, 64.0f)), Vec2(0.0f, 0.0f), true));
	wall1->AddComponent(new DrawComponent());

	Entity* wall2 = new Entity("WALL", entityState::IDLE);
	wall2->AddComponent(new SpatialComponent(new Quad(Vec2(64.0f, 64.0f)), Vec2(365.0f, 300.0f), true));
	wall2->AddComponent(new DrawComponent());

	Entity* wall3 = new Entity("WALL", entityState::IDLE);
	wall3->AddComponent(new SpatialComponent(new Quad(Vec2(64.0f, 64.0f)), Vec2(300.0f, 365.0f), true));
	wall3->AddComponent(new DrawComponent());

	Entity* sky = new Entity("SKY", entityState::IDLE);
	sky->AddComponent(new SpatialComponent(new Quad(Vec2(0.0f, 0.0f)), Vec2(0.0f, 0.0f),false));
	sky->AddComponent(new DrawComponent());



	lvl->AddEntity(cursor);
	lvl->AddEntity(player);
	lvl->AddEntity(wall1);
	lvl->AddEntity(wall2);
	lvl->AddEntity(wall3);
	lvl->AddEntity(sky);


	return lvl;
}