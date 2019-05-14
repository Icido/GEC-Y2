#pragma once
#include "Vector2.h"
#include <string>
#include <ostream>

enum class Faction
{
	isPlayer, isEnemy, isNeutral, isBackground
};

class Visualisation;
class World;

class Entity
{
private:
	//Current position and old position, used to lerp the position and rendering between movement
	Vector2 m_position{};
	Vector2 m_oldPosition{};

protected:
	//Protected entity variables used by all the children that inherit this base class
	Vector2 initialPos{};
	bool m_alive{ true };
	double m_animationTime{};
	double m_lastTimeUpdatedAnimation{ 0 };
	float m_speed{};
	float m_verticalSpeed{};
	int m_damageInflicted{};
	int m_health{};
	int m_frameNum{ 0 };
	int m_score{};
	int m_numFrames{ 1 };
	int m_maxHealth{};
	std::string m_spriteName;

public:
	Entity(std::string spriteName, int numFrames = 1);
	virtual ~Entity();

	//Renders the entity at its position (or position between current and old position).
	void Render(Visualisation &viz, float lerpTime);

	//Checks whether this entity and the parameter entity can collide by comparing rectangles
	void checkCollision(World &world, Visualisation &viz, Entity &otherEntity);

	//Checks whether this entity and the parameter entity can collide by comparing sides.
	bool canCollideWith(Entity &otherEntity);

	//Calculates the damage inflicted on both sides when two entities collide.
	void takeDamage(World &world, int damageInflicted);

	//Respawns the entity at its initial position, initial health and sets it back to "Alive".
	virtual void respawn() { setPosition(initialPos); m_health = m_maxHealth; m_alive = true; }

	//Updates the entity. This function is then called within each entity as well.
	virtual void Update(World& world) = 0;
	
	virtual bool isAlive() { return m_alive; }
	virtual int getScore() { return m_score; }
	virtual float getSpeed() { return m_speed; }
	virtual Faction getSide() const = 0;
	virtual Vector2 getPosition() const { return m_position; }

	virtual void setPosition(Vector2 newPosition) { m_oldPosition = m_position; m_position = newPosition; }
	virtual void setPosition(float newPosX, float newPosY) { m_position.x = newPosX; m_position.y = newPosY; }
	virtual void setAnimationTime(double newTime) { m_animationTime = newTime; }
	virtual void setAnimationFrames(int newFrames) { m_numFrames = newFrames; }
	virtual void setDamageInflicted(int newDamage) { m_damageInflicted = newDamage; }
	virtual void setHealth(int newHealth) { m_health = newHealth; }
	virtual void setMaxHealth(int newMaxHealth) { m_maxHealth = newMaxHealth; }
	virtual void setSpeed(float newSpeed) { m_speed = newSpeed; }
	virtual void setVerticalSpeed(float newSpeed) { m_verticalSpeed = newSpeed; }
	virtual void setScore(int newScore) { m_score = newScore; }
};

