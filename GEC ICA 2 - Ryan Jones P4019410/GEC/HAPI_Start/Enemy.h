#pragma once
#include "Entity.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Enemy :
	public Entity
{
public:
	Enemy(std::string spriteName, int numFrames = 1);
	~Enemy();

	Faction getSide() const override final
	{
		return Faction::isEnemy;
	}

	//Initial position and loopBack boolean checks
	bool initPos = true;
	bool loopBack = false;

	//Shooting variables
	DWORD enemyShootCooldown = 2000;
	DWORD enemyShootTimer = 0;
	DWORD enemyDeltaTime = 0;

	void Update(World& world) override final;
};