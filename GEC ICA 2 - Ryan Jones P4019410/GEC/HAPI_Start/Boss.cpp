#include "Boss.h"
#include "World.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

Boss::Boss(std::string spriteName, int numFrames) : Entity(spriteName)
{
	//Sets the values when the entity is created
	setAnimationFrames(numFrames);
	setAnimationTime(300);
	setHealth(20);
	setMaxHealth(20);
	setSpeed(5);
	setDamageInflicted(1);
	setScore(20);
	if (!HAPI.LoadSound("data\\MajorDeath.wav"))
	{
		HAPI.UserMessage("Sound MajorDeath.wav not loaded!", "Warning: No sound found!");
		return;
	}
}


Boss::~Boss()
{
}

void Boss::Update(World& world)
{
	//Getting the initial position ONCE
	if (initPos)
	{
		initialPos = getPosition();
		initPos = false;
	}

	//If the boss dies, play the sound and lower its health further to prevent replaying the sound again until it respawns.
	if (m_health == 0)
	{
		HAPI.PlaySound("data\\MajorDeath.wav");
		m_health--;
	}


	//Enemy AI here (path following, etc)
	Vector2 pos(getPosition());

	//Moves the boss up and down from its initial position.
	if (!loopBack)
	{
		if (pos.y < (initialPos.y + 200))
		{
			pos.y += (m_speed / 2);
		}
		else
		{
			loopBack = true;
		}
	}
	else
	{
		if (pos.y > (initialPos.y - 200))
		{
			pos.y -= (m_speed / 2);
		}
		else
		{
			loopBack = false;
		}
	}

	//Moves the boss left every update, until it reaches its destination where it stays on screen.
	if (pos.x > 600)
	{
		pos.x -= m_speed;
	}

	setPosition(pos);

	//If the boss is on screen, start shooting.
	if (m_alive && pos.x < 1024)
	{
		bossShootTimer = HAPI.GetTime() - bossDeltaTime;
		if (bossShootTimer > bossShootCooldown)
		{
			world.fireBullet(getSide(), getPosition(), Vector2(-1, 0) * 20.f, 1);
			bossShootTimer = 0;
			bossDeltaTime = HAPI.GetTime();
		}
	}
}