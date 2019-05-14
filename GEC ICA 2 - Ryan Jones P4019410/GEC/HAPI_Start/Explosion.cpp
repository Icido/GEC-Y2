#include "Explosion.h"
#include "World.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

Explosion::Explosion(std::string spriteName, int numFrames) : Entity(spriteName)
{
	//Sets the values when the entity is created
	setAnimationFrames(numFrames);
	setAnimationTime(100);
	setHealth(100);
	setDamageInflicted(0);
	m_alive = false;
	if (!HAPI.LoadSound("data\\Explosion.wav"))
	{
		HAPI.UserMessage("Sound Explosion.wav not loaded!", "Warning: No sound found!");
		return;
	}
}

Explosion::~Explosion()
{
}

void Explosion::Update(World& world)
{
	explosionTimer = HAPI.GetTime() - explosionDeltaTime;
	if (explosionTimer > explosionLifeTime)
	{	
		explosionTimer = 0;
		explosionDeltaTime = HAPI.GetTime();
		m_alive = false;
	}
	
}

void Explosion::explode(const Vector2 &position)
{
	HAPI.PlaySound("data\\Explosion.wav");
	setPosition(position);
	m_alive = true;
	
}