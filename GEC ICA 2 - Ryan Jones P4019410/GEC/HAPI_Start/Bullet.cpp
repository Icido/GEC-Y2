#include "Bullet.h"
#include "World.h"


Bullet::Bullet(std::string spriteName, int numFrames) : Entity(spriteName)
{
	//Sets the values when the entity is created
	setAnimationFrames(numFrames);
	setAnimationTime(100);
	m_alive = false;
	m_health = 1;
	if (!HAPI.LoadSound("data\\Laser.wav"))
	{
		HAPI.UserMessage("Sound Laser.wav not loaded!", "Warning: No sound found!");
		return;
	}

}


Bullet::~Bullet()
{
}

void Bullet::Update(World& world)
{
	//Moves the bullet with respect to the direction given.
	setPosition(getPosition() + m_direction);
	
	Vector2 currentPos(getPosition());

	//Clamps the bullet to within the screen space, allowing a small adjustment along the x=0 and y=0 axis for bullet clipping.
	if (currentPos.x > 1024 || currentPos.x < -32 || currentPos.y > 1024 || currentPos.y < -32)
		m_alive = false;
	
}

void Bullet::Spawn(Faction side, const Vector2 &position, const Vector2 &direction, int damageInflicted)
{
	//Spawns the bullet with respect to the side/position it is fired from.
	HAPI.PlaySound("data\\Laser.wav");
	m_side = side;
	m_direction = direction;
	setPosition(position.x + 32, position.y + 32);
	m_damageInflicted = damageInflicted;
	m_alive = true;
}
