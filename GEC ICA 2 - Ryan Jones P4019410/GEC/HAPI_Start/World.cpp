#include "World.h"
#include "Visualisation.h"
#include "Entity.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Boss.h"
#include "Wall.h"
#include "Explosion.h"
#include "Bullet.h"

#include <cassert>
#include <string>

World::~World()
{
	delete m_Vis;

	for (auto p : m_entityVector)
		delete p;
}

bool World::loadLevel()
{
#pragma region "Sound loading"
	if (!HAPI.LoadSound("data\\MajorDeath.wav"))
	{
		HAPI.UserMessage("Sound MajorDeath.wav not loaded!", "Warning: No sound found!");
		return false;
	}

	if (!HAPI.LoadSound("data\\Respawn.wav"))
	{
		HAPI.UserMessage("Sound Respawn.wav not loaded!", "Warning: No sound found!");
		return false;
	}

	if (!HAPI.LoadSound("data\\Pause.wav"))
	{
		HAPI.UserMessage("Sound Pause.wav not loaded!", "Warning: No sound found!");
		return false;
	}
#pragma endregion
	
#pragma region "Texture loading"
	//Arrays start at 0
	//m_entityVector[0 - 1]
	if (!m_Vis->createSprite("data\\spaceBackground.jpg", "Space"))
		return false;

	Background* backgroundEntity1 = new Background("Space");
	m_entityVector.push_back(backgroundEntity1);

	Background* backgroundEntity2 = new Background("Space");
	m_entityVector.push_back(backgroundEntity2);

	//m_entityVector[2-100]
	if (!m_Vis->createSprite("data\\Box.png", "Wall"))
		return false;

	m_wallStartIndex = m_entityVector.size();

	for (int i = 0; i < kNumWalls; i++)
	{
		Wall* wallEntity = new Wall("Wall");
		m_entityVector.push_back(wallEntity);
	}

	//m_entityVector[101]
	if (!m_Vis->createSprite("data\\betterSpaceship.png","Player", 4))
		return false;

	Player* playerEntity = new Player("Player", 4);
	m_entityVector.push_back(playerEntity);


	//m_entityVector[102]
	if (!m_Vis->createSprite("data\\BossEnemy.png", "Boss", 2))
		return false;

	Boss* bossEntity = new Boss("Boss", 2);
	m_entityVector.push_back(bossEntity);


	//m_entityVector[103-112]
	if (!m_Vis->createSprite("data\\RegularEnemy.png", "Enemy", 2))
		return false;

	m_enemyStartIndex = m_entityVector.size();

	for (int i = 0; i < kNumEnemies; i++)
	{
		Enemy* enemyEntity = new Enemy("Enemy", 2);
		m_entityVector.push_back(enemyEntity);
	}


	//m_entityVector[113-132]
	if (!m_Vis->createSprite("data\\Explosion.png", "Explosion", 4))
		return false;

	m_explosionStartIndex = m_entityVector.size();

	for (int i = 0; i < kNumExplosions; i++)
	{
		Explosion* explosionEntity = new Explosion("Explosion", 4);
		m_entityVector.push_back(explosionEntity);
	}


	//m_entityVector[133-332]
	if (!m_Vis->createSprite("data\\LaserBullet.png", "Bullet", 2))
		return false;

	m_bulletStartIndex = m_entityVector.size();

	for (int i = 0; i < kNumBullets; i++)
	{
		Bullet* bulletEntity = new Bullet("Bullet", 2);
		m_entityVector.push_back(bulletEntity);
	}
#pragma endregion

	//Level initial positions

	backgroundEntity1->setPosition(0, 0);
	backgroundEntity2->setPosition(1023, 0);
	playerEntity->setPosition(Vector2(100, 480));

	//Level walls
#pragma region "Level Walls"

	//Bottom floor
	m_entityVector[2]->setPosition(0, 960);

	m_entityVector[3]->setPosition(64, 960);

	m_entityVector[4]->setPosition(128, 960);

	m_entityVector[5]->setPosition(192, 960);
	m_entityVector[6]->setPosition(192, 896); 

	m_entityVector[7]->setPosition(256, 960);
	m_entityVector[8]->setPosition(256, 896);

	m_entityVector[9]->setPosition(320, 960);
	m_entityVector[10]->setPosition(320, 896);

	m_entityVector[11]->setPosition(384, 960);
	m_entityVector[12]->setPosition(384, 896);

	m_entityVector[13]->setPosition(448, 960);
	m_entityVector[14]->setPosition(448, 896);
	m_entityVector[15]->setPosition(448, 832);
	m_entityVector[16]->setPosition(448, 768);
	m_entityVector[17]->setPosition(448, 704);

	m_entityVector[18]->setPosition(512, 960);
	m_entityVector[19]->setPosition(512, 896);
	m_entityVector[20]->setPosition(512, 832);
	m_entityVector[21]->setPosition(512, 768);
	m_entityVector[22]->setPosition(512, 704);

	m_entityVector[23]->setPosition(576, 960);
	m_entityVector[24]->setPosition(576, 896);
	m_entityVector[25]->setPosition(576, 832);
	m_entityVector[26]->setPosition(576, 768);
	m_entityVector[27]->setPosition(576, 704);
	m_entityVector[28]->setPosition(576, 640);
	m_entityVector[29]->setPosition(576, 576);

	m_entityVector[30]->setPosition(640, 960);
	m_entityVector[31]->setPosition(640, 896);
	m_entityVector[32]->setPosition(640, 832);
	m_entityVector[33]->setPosition(640, 768);
	m_entityVector[34]->setPosition(640, 704);
	m_entityVector[35]->setPosition(640, 640);
	m_entityVector[36]->setPosition(640, 576);
	m_entityVector[37]->setPosition(640, 512);
	m_entityVector[38]->setPosition(640, 448);

	m_entityVector[39]->setPosition(704, 960);
	m_entityVector[40]->setPosition(704, 896);
	m_entityVector[41]->setPosition(704, 832);
	m_entityVector[42]->setPosition(704, 768);

	m_entityVector[43]->setPosition(768, 960);
	m_entityVector[44]->setPosition(768, 896);
	m_entityVector[45]->setPosition(768, 832);

	m_entityVector[46]->setPosition(832, 960);

	m_entityVector[47]->setPosition(896, 960);

	m_entityVector[48]->setPosition(960, 960);

	m_entityVector[49]->setPosition(1024, 960);


	
	
	//Top floor
	m_entityVector[50]->setPosition(0, 64);
	m_entityVector[51]->setPosition(0, 128);
	m_entityVector[52]->setPosition(0, 192);
	m_entityVector[53]->setPosition(0, 256);

	m_entityVector[54]->setPosition(64, 64);
	m_entityVector[55]->setPosition(64, 128);
	m_entityVector[56]->setPosition(64, 192);
	m_entityVector[57]->setPosition(64, 256);

	m_entityVector[58]->setPosition(128, 64);
	m_entityVector[59]->setPosition(128, 128);
	m_entityVector[60]->setPosition(128, 192);
	m_entityVector[61]->setPosition(128, 256);

	m_entityVector[62]->setPosition(192, 64);

	m_entityVector[63]->setPosition(256, 64);
	m_entityVector[64]->setPosition(256, 128);

	m_entityVector[65]->setPosition(320, 64);
	m_entityVector[66]->setPosition(320, 128);

	m_entityVector[67]->setPosition(384, 64);

	m_entityVector[68]->setPosition(448, 64);
	m_entityVector[69]->setPosition(448, 128);
	m_entityVector[70]->setPosition(448, 192);
	m_entityVector[71]->setPosition(448, 256);

	m_entityVector[72]->setPosition(512, 64);
	m_entityVector[73]->setPosition(512, 128);
	m_entityVector[74]->setPosition(512, 192);


	m_entityVector[75]->setPosition(576, 64);
	m_entityVector[76]->setPosition(576, 128);

	m_entityVector[77]->setPosition(640, 64);

	m_entityVector[78]->setPosition(704, 64);

	m_entityVector[79]->setPosition(768, 64);

	m_entityVector[80]->setPosition(832, 64);
	m_entityVector[81]->setPosition(832, 128);

	m_entityVector[82]->setPosition(896, 64);
	m_entityVector[83]->setPosition(896, 128);
	m_entityVector[84]->setPosition(896, 192);
	m_entityVector[85]->setPosition(896, 256);
	m_entityVector[86]->setPosition(896, 320);
	m_entityVector[87]->setPosition(896, 384);
	m_entityVector[88]->setPosition(896, 448);
	m_entityVector[89]->setPosition(896, 512);

	m_entityVector[90]->setPosition(960, 64);
	m_entityVector[91]->setPosition(960, 128);
	m_entityVector[92]->setPosition(960, 192);
	m_entityVector[93]->setPosition(960, 256);
	m_entityVector[94]->setPosition(960, 320);
	m_entityVector[95]->setPosition(960, 384);
	m_entityVector[96]->setPosition(960, 448);
	m_entityVector[97]->setPosition(960, 512);
	m_entityVector[98]->setPosition(960, 576);

	m_entityVector[99]->setPosition(1024, 64);
	m_entityVector[100]->setPosition(1024, 128);
#pragma endregion

	//Waves 1-4 - Enemies
#pragma region "Enemies"
	//Wave 1 - 1 Enemy
	m_entityVector[103]->setPosition(1500, 516);

	//Wave 2 - 2 Enemies
	m_entityVector[104]->setPosition(2000, 484);
	m_entityVector[105]->setPosition(2000, 548);

	//Wave 3 - 3 Enemies
	m_entityVector[106]->setPosition(2500, 452);
	m_entityVector[107]->setPosition(2500, 516);
	m_entityVector[108]->setPosition(2500, 580);

	//Wave 4 - 4 Enemies
	m_entityVector[109]->setPosition(3000, 420);
	m_entityVector[110]->setPosition(3000, 484);
	m_entityVector[111]->setPosition(3000, 548);
	m_entityVector[112]->setPosition(3000, 612);
#pragma endregion

	//Wave 5 - 1 Boss
	bossEntity->setPosition(4000, 516);

	//Sets the background music to loop
	musicOptions.loop = true;

	return true;
}

void World::run()
{
	m_Vis = new Visualisation;
	
	//Loads the level - if it is false, return and exit the application.
	if (!loadLevel())
	{
		HAPI.UserMessage("Level not loaded!", "Warning: No level found!");
		return;
	}

	//Receiving the screens pointer and rectangle
	BYTE* screen = m_Vis->getScreenPointer();
	Rectangle screenRect = m_Vis->getScreenRect();

	//Sets the icon as screen (not able to implement gameIcon in time)
	if (!HAPI.SetIcon(screen, 64, 64))
	{
		HAPI.UserMessage("Icon texture not loaded!", "Warning: No texture found!");
		return;
	}

	//Background music
	if (!HAPI.PlayStreamedMedia("data\\Level-Music.mp3", musicOptions, musicID))
	{
		HAPI.UserMessage("Sound Level-Music.mp3 not loaded!", "Warning: No sound found!");
		return;
	}

	//Game Loop
	while (HAPI.Update())
	{
		//Controller data
		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);
		if (!controllerData.isAttached)
		{
			HAPI.RenderText(0, 0, HAPI_TColour::YELLOW, HAPI_TColour::RED, 1, "Controller unplugged!", 40, eBold);
		}

		//Screenshot
		if (keyboardData.scanCode['L'] || (controllerData.digitalButtons[HK_DIGITAL_LEFT_THUMB] && controllerData.digitalButtons[HK_DIGITAL_RIGHT_THUMB]))
		{
			std::string ssNum = std::to_string(HAPI.GetTime());
			HAPI.SaveImage(screen, screenRect.Width(), screenRect.Height(), "data\\Screenshot_" + ssNum + ".png");
			HAPI.RenderText(0, 1000, HAPI_TColour::WHITE, "Screenshot taken", 12);
		}

#pragma region "Game state management"
		//Game state management

		//If player dies, respawn player with one less life.
		if ((numLives > 0) && !m_entityVector[101]->isAlive())
		{
			HAPI.PlaySound("data\\MajorDeath.wav");
			m_entityVector[101]->respawn();
			numLives--;
		}

		//If boss dies, restart waves with more speed.
		if ((numLives > 0) && !m_entityVector[102]->isAlive())
		{
			HAPI.PlaySound("data\\Respawn.wav");
			for (int i = 102; i < 112; i++)
			{
				m_entityVector[i]->respawn();
				m_entityVector[i]->setSpeed(m_entityVector[i]->getSpeed() + 1);
			}
		}
		
		//If player dies and player has no more lives left - GAME OVER
		if ((numLives < 1) && !m_entityVector[101]->isAlive())
		{
			std::string finalScore = std::to_string(currentScore);
			HAPI.RenderText(350, 100, HAPI_TColour::BLUE, HAPI_TColour::WHITE, 1, "Score:" + finalScore, 72);
			HAPI.RenderText(275, 200, HAPI_TColour::RED, HAPI_TColour::WHITE, 1, "GAME OVER", 72);
			HAPI.RenderText(125, 300, HAPI_TColour::WHITE, "Press RETURN or 'START' to continue", 48);
			HAPI.RenderText(350, 400, HAPI_TColour::WHITE, "Press ESCAPE or 'BACK' to exit", 32);
			isGameOver = true;

			if (keyboardData.scanCode[HK_ESCAPE] || controllerData.digitalButtons[HK_DIGITAL_BACK])
				return;
		}
		
		//Restarting the game
		if ((keyboardData.scanCode[HK_RETURN] || controllerData.digitalButtons[HK_DIGITAL_START]) && isGameOver)
		{
			if (currentScore > highScore)
			{
				highScore = currentScore;
			}
			HAPI.PlaySound("data\\Respawn.wav");
			numLives = 2;
			currentScore = 0;
			for (int i = 101; i < 112; i++)
			{
				m_entityVector[i]->respawn();
			}
			isGameOver = false;
		}

		//Pausing
		if ((keyboardData.scanCode[HK_RETURN] || controllerData.digitalButtons[HK_DIGITAL_START]) && !isGameOver)
		{
			HAPI.PlaySound("data\\Pause.wav");
			isPaused = !isPaused;
		}

		if (isPaused)
		{
			HAPI.RenderText(400, 500, HAPI_TColour::GREEN, "PAUSED", 40);
		}
#pragma endregion

#pragma region "World Update"
		//Update World
		auto currentTime = HAPI.GetTime();

		m_timeAfterTick = currentTime - m_deltaTime;

		if (!isPaused)
		{
			if (m_timeAfterTick >= m_gameTick)
			{
				updateWorld(*this);
				m_deltaTime = currentTime;
				m_lerpTime = 0;


				for (int i = 0; i < m_entityVector.size(); i++)
				{
					for (int j = i + 1; j < m_entityVector.size(); j++)
					{
						m_entityVector[i]->checkCollision(*this, *m_Vis, *m_entityVector[j]);
					}
				}

				m_timeAfterTick = 0;
			}
			m_lerpTime = m_timeAfterTick / (float)m_gameTick;
			assert(m_lerpTime >= 0 && m_lerpTime <= 1.0f);
		}
#pragma endregion

#pragma region "Rendering"
		//Rendering
		m_Vis->fastColourClear(HAPI_TColour(0, 30, 0));
		
		std::string totalScore = std::to_string(currentScore);

		HAPI.RenderText(400, 10, HAPI_TColour::WHITE, "SCORE: " + totalScore, 20);

		if (currentScore > highScore)
		{
			HAPI.RenderText(600, 10, HAPI_TColour::WHITE, "HIGH SCORE: " + totalScore, 20);
		}
		else
		{
			std::string currentHighScore = std::to_string(highScore);
			HAPI.RenderText(600, 10, HAPI_TColour::WHITE, "HIGH SCORE: " + currentHighScore, 20);
		}
		std::string playerLives = std::to_string(numLives + 1);
		HAPI.RenderText(900, 10, HAPI_TColour::WHITE, "Lives: " + playerLives, 20);

		for (auto p : m_entityVector)
			p->Render(*m_Vis, m_lerpTime);

#pragma endregion

	}
}

void World::updateWorld(World& world)
{
	//Loops through the entity vector and updates each entity.
	for (auto p : m_entityVector)
		p->Update(world);
}

void World::fireBullet(const Faction &side, const Vector2 &pos, const Vector2 &dir, int damage)
{
	//Loops through the entity vector to find a bullet that is dead and spawns it at given position.
	for (size_t i = m_bulletStartIndex; i < m_bulletStartIndex + kNumBullets; i++)
	{
		if (!m_entityVector[i]->isAlive())
		{
			((Bullet*)(m_entityVector[i]))->Spawn(side, pos, dir, damage);
			return;
		}
	}
	std::cout << "Ran out of bullets!" << std::endl;
}

void World::fireExplosion(const Vector2 &pos)
{
	//Loops through the entity vector to find an explosion that is dead and spawns it at given position.
	for (size_t i = m_explosionStartIndex; i < m_explosionStartIndex + kNumExplosions; i++)
	{
		if (!m_entityVector[i]->isAlive())
		{
			((Explosion*)(m_entityVector[i]))->explode(pos);
			return;
		}
	}
	std::cout << "Ran out of explosions!" << std::endl;
}