#pragma once
#include "Entity.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Explosion :
	public Entity
{
public:
	Explosion(std::string spriteName, int numFrames = 1);
	~Explosion();

	Faction getSide() const override final
	{
		return Faction::isBackground;
	}

	void explode(const Vector2 & position);

	DWORD explosionTimer = 0;
	DWORD explosionDeltaTime = 0;
	DWORD explosionLifeTime = 200;

	void Update(World& world) override final;
};

