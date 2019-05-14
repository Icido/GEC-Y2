#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{
private:
	Faction m_side{ Faction::isNeutral };
public:
	Bullet(std::string spriteName, int numFrames = 1);
	~Bullet();

	Faction getSide() const override final
	{
		return m_side;
	}

	Vector2 m_direction{};

	//Spawns a bullet with respect to side, & position, given direction and damage infliced upon collision.
	void Spawn(Faction side, const Vector2 &position, const Vector2 &direction, int damageInflicted);

	void Update(World& world) override final;
};

