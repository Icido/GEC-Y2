#include "Enemy.h"
#include "World.h"


Enemy::Enemy(std::string spriteName, int numFrames) : Entity(spriteName)
{
	//Sets the values when the entity is created
	setAnimationFrames(numFrames);
	setAnimationTime(100);
	setHealth(2);
	setMaxHealth(2);
	setSpeed(5);
	setVerticalSpeed((float)(rand() % 30 + 10));
	setDamageInflicted(1);
	setScore(1);
	if (!HAPI.LoadSound("data\\Death.wav"))
	{
		HAPI.UserMessage("Sound Death.wav not loaded!", "Warning: No sound found!");
		return;
	}
}


Enemy::~Enemy()
{
}

void Enemy::Update(World& world)
{
	//Getting the initial position ONCE
	if (initPos)
	{
		initialPos = getPosition();
		initPos = false;
	}

	//Upon death, play the death sound and lower the health further to prevent replaying the sound again until it respawns.
	if (m_health == 0)
	{
		HAPI.PlaySound("data\\Death.wav");
		m_health--;
	}

	//Enemy AI here (path following, etc)
	Vector2 pos(getPosition());

	//Loops the enemy up and down from its initial position every update.
	if (!loopBack)
	{
		if (pos.y < (initialPos.y + 200))
		{
			pos.y += (m_verticalSpeed / 2);
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
			pos.y -= (m_verticalSpeed / 2);
		}
		else
		{
			loopBack = false;
		}
	}

	//Moves the enemy left every update.
	pos.x -= m_speed;

	setPosition(pos);

	//If the enemy is on screen, start shooting.
	if (m_alive && pos.x < 1024)
	{
		enemyShootTimer = HAPI.GetTime() - enemyDeltaTime;
		if (enemyShootTimer > enemyShootCooldown)
		{
			world.fireBullet(getSide(), getPosition(), Vector2(-1, 0) * 20.f, 1);
			enemyShootTimer = 0;
			enemyDeltaTime = HAPI.GetTime();
		}
	}
}
