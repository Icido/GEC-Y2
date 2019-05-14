#pragma once
#include "Entity.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Boss :
	public Entity
{
public:
	Boss(std::string spriteName, int numFrames = 1);
	~Boss();

	Faction getSide() const override final
	{
		return Faction::isEnemy;
	}

	//Initial position and loopBack boolean checks
	bool initPos = true;
	bool loopBack = false;

	//Shooting variables
	DWORD bossShootCooldown = 750;
	DWORD bossShootTimer = 0;
	DWORD bossDeltaTime = 0;

	void Update(World& world) override final;
};