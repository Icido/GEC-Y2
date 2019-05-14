#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"
#include "World.h"

#include <algorithm>

Entity::Entity(std::string spriteName, int numFrames) : m_spriteName(spriteName), m_numFrames(numFrames)
{
}

Entity::~Entity()
{
}

void Entity::Render(Visualisation &vis, float lerpTime)
{	
	if (!m_alive)
		return;

	//Calculates where the current position would be from the old and new positions and time of LERP.
	Vector2 interPos{ m_oldPosition + (m_position - m_oldPosition) * lerpTime };

	//Uses the Visualisation to render the sprite at the current position.
	vis.renderSprite(m_spriteName, (int)m_position.x, (int)m_position.y, m_frameNum);

	//Updates which frame of animation is being currently used.
	if (HAPI.GetTime() - m_lastTimeUpdatedAnimation >= m_animationTime)
	{
		m_frameNum++;
		if (m_frameNum >= m_numFrames)
			m_frameNum = 0;

		m_lastTimeUpdatedAnimation = HAPI.GetTime();
	}

}

void Entity::checkCollision(World &world, Visualisation &viz, Entity &otherEntity)
{
	//If the two entities can't collide with sides, exit the function.
	if (!canCollideWith(otherEntity))
		return;

	if (this->m_alive && otherEntity.m_alive)
	{

		Rectangle thisRect{ viz.getRectangle(m_spriteName) };
		Rectangle otherRect{ viz.getRectangle(otherEntity.m_spriteName) };

		thisRect.translate((int)m_position.x, (int)m_position.y);
		otherRect.translate((int)otherEntity.m_position.x, (int)otherEntity.m_position.y);

		if (!thisRect.isCompletelyOutsideOf(otherRect))
		{
			//Collision occurs
			takeDamage(world, otherEntity.m_damageInflicted);
			otherEntity.takeDamage(world, m_damageInflicted);
		}
	}
}


bool Entity::canCollideWith(Entity &otherEntity)
{
	//Checks between each player/enemy and player/neutral collisions. All other combinations do not collide.
	if (getSide() == Faction::isPlayer && otherEntity.getSide() == Faction::isEnemy)
		return true;
	
	if (getSide() == Faction::isEnemy && otherEntity.getSide() == Faction::isPlayer)
		return true;

	if (getSide() == Faction::isPlayer && otherEntity.getSide() == Faction::isNeutral)
		return true;

	if (getSide() == Faction::isNeutral && otherEntity.getSide() == Faction::isPlayer)
		return true;

	return false;
}

void Entity::takeDamage(World &world, int damageInflicted)
{
	m_health -= damageInflicted;

	if (m_health <= 0)
	{
		m_alive = false;
		world.currentScore += m_score;
		world.fireExplosion(m_position);
	}
}