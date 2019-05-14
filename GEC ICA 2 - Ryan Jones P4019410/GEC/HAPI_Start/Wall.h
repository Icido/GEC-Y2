#pragma once
#include "Entity.h"
class Wall :
	public Entity
{
public:
	Wall(std::string spriteName, int numFrames = 1);
	~Wall();

	Faction getSide() const override final 
	{
		return Faction::isNeutral; 
	}

	void Update(World& world) override final;
};

