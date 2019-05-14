#pragma once
#include <HAPI_lib.h>
#include <algorithm>
#include "Vector2.h"

using namespace HAPISPACE;

class Visualisation;
class Entity;
enum class Faction;

class World
{
private:
	Visualisation *m_Vis{ nullptr };
	//Vector of entities used to store all entities within the world
	std::vector<Entity*> m_entityVector;

	//Variable sized value to show where the start of the index of all the same entity is.
	//Better to use it like this instead of naming each entity individually, especially if using 99 walls and 10 enemies.
	size_t m_wallStartIndex{ 0 };
	size_t m_enemyStartIndex{ 0 };
	size_t m_bulletStartIndex{ 0 };
	size_t m_explosionStartIndex{ 0 };
public:
	World() = default;
	~World();

	//Mouse and keyboard data
	const HAPI_TMouseData &mouseData = HAPI.GetMouseData();
	const HAPI_TKeyboardData &keyboardData = HAPI.GetKeyboardData();

	//Game tick variables
	const DWORD m_gameTick = 50;
	float m_lerpTime = 0.f;
	DWORD m_deltaTime = 0;
	DWORD m_timeAfterTick = 0;

	//Constant integers of how many number of Walls/Bullets etc should be in the world.
	const int kNumWalls = 99;
	const int kNumBullets = 200;
	const int kNumExplosions = 20;
	const int kNumEnemies = 10;

	//Background music ID and media options.
	int musicID;
	HAPI_TStreamedMediaOptions musicOptions;

	//Score and lives integers
	int currentScore;
	int highScore = 0;
	int numLives = 2;

	//Game state management booleans
	bool isPaused = false;
	bool isGameOver = false;

	//Functions used to load and run the world
	bool loadLevel();
	void run();
	void updateWorld(World& world);

	//Functions used to revive and spawn bullets and explosions when certain conditions are met, otherwise the bullets and explosions are dead.
	void fireBullet(const Faction &side, const Vector2 &pos, const Vector2 &dir, int damage);
	void fireExplosion(const Vector2 &pos);
};

