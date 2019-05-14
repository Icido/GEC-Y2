#include "Player.h"
#include "World.h"
#include <HAPI_lib.h>
#include <string>
#include <cassert>

using namespace HAPISPACE;

Player::Player(std::string spriteName, int numFrames) : Entity(spriteName)
{
	//Sets the values when the entity is created
	setAnimationFrames(numFrames);
	setAnimationTime(300);
	setHealth(1);
	setMaxHealth(1);
	setSpeed(15);
	setDamageInflicted(0);
}

Player::~Player()
{
}

void Player::Update(World& world)
{
	//Getting the initial position ONCE
	if (initPos)
	{
		initialPos = getPosition();
		initPos = false;
	}

	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	Vector2 pos(getPosition());

	if (keyboardData.scanCode['W'] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 10000))
		pos.y -= m_speed;
		
	if (keyboardData.scanCode['A'] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -10000))
		pos.x -= m_speed;

	if (keyboardData.scanCode['S'] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -10000))
		pos.y += m_speed;
		
	if (keyboardData.scanCode['D'] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 10000))
		pos.x += m_speed;

	if (pos.x <= 0)
		pos.x = 0;

	if (pos.x >= 960)
		pos.x = 960;

	setPosition(pos);

	if (keyboardData.scanCode[HK_SPACE] || (controllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > 30))
	{
		if (m_alive)
		{
			playerShootTimer = HAPI.GetTime() - playerDeltaTime;
			if (playerShootTimer > playerShootCooldown)
			{
				world.fireBullet(getSide(), getPosition(), Vector2(1, 0) * 20.f, 1);
				playerShootTimer = 0;
				playerDeltaTime = HAPI.GetTime();
			}
		}
	}

	if(!m_alive)
		HAPI.SetControllerRumble(0, 30000, 30000);
	else
		HAPI.SetControllerRumble(0, 0, 0);

}
