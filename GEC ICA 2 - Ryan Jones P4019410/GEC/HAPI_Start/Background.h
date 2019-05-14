#pragma once
#include "Entity.h"
class Background :
	public Entity
{
public:
	Background(std::string spriteName);
	~Background();

	//Background side entities don't affect anything and are not affected by anything.
	Faction getSide() const override final
	{
		return Faction::isBackground;
	}

	void Update(World& world) override final;
};

