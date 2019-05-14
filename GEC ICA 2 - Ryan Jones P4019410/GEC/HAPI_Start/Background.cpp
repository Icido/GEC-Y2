#include "Background.h"
#include "World.h"


Background::Background(std::string spriteName) : Entity(spriteName)
{
	setSpeed(1);
}


Background::~Background()
{
}

void Background::Update(World& world)
{
	Vector2 pos(getPosition());

	//Moves the background texture left every update
	//Loops the background back to the right hand side off-screen.
	if (pos.x >= -1023)
	{
		pos.x -= m_speed;
	}
	else
	{
		pos.x = 1023;
	}

	setPosition(pos);
}
