#pragma once
#include "Entity.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Player :
	public Entity
{
public:
	Player(std::string spriteName, int numFrames = 1);
	~Player();

	const HAPI_TKeyboardData &keyboardData = HAPI.GetKeyboardData();
	Faction getSide() const override final
	{
		return Faction::isPlayer;
	}

	//Initial position boolean check
	bool initPos = true;

	//Shooting variables
	DWORD playerShootCooldown = 250;
	DWORD playerShootTimer = 0;
	DWORD playerDeltaTime = 0;

	void Update(World& world) override final;
};
