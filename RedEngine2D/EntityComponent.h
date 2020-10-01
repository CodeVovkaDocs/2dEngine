#pragma once
enum class entityComponentType
{
	SPATIAL,
	MOVEMENT,
	CONTROL,
	DRAW
};

class EntityComponent
{
public:

	EntityComponent() {};

	virtual entityComponentType GetType() = 0;

	virtual ~EntityComponent() {};
};

