#include "Wall.h"
#include "World.h"


Wall::Wall(std::string spriteName, int numFrames) : Entity(spriteName)
{
	//Sets the values when the entity is createds
	setHealth(1000);
	setMaxHealth(1000);
	setDamageInflicted(1);
	setSpeed(3);

	//Default position of this texture if it is not in use
	setPosition(0, -64);
}


Wall::~Wall()
{
}

void Wall::Update(World& world)
{
	Vector2 pos(getPosition());
	
	//Moves the background texture left every update
	//Loops the background back to the right hand side off-screen.
	if (pos.x > -63)
	{
		pos.x -= m_speed;
	}
	else
	{
		pos.x = 1024;
	}

	setPosition(pos);

}