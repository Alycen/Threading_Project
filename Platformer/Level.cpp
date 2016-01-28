#include "Level.h"
#include "Sprite.h"

const int Level::SCALE = 32;
const int BlockWidth = 45;
const int BlockHeight = 51;
using namespace std;

Level::Level()
{
}


void Level::LoadLevel(std::string name, b2World * world)
{

	std::vector<std::string> map = Level::LoadFromTextFile(name);
	const int mapX = 81;
	const int mapY = 23;

	SDL_Rect source = { 0, 0, 100, 100 };

	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			char c = (char)map[y][x];
			if (c == 'L')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left2.png", "EndPlatform");
			}

			if (c == 'R')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right2.png", "EndPlatform");
			}

			if (c == 'M')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle2.png", "platform");
			}

			if (c == 'P')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left1.png", "EndPlatform");

			}

			if (c == 'O')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle3.png", "platform");
			}

			if (c == 'I')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right1.png", "EndPlatform");
			}
			if (c == 'U')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left3.png", "EndPlatform");
			}

			if (c == 'Y')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle3.png", "platform");
			}

			if (c == 'T')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right3.png", "EndPlatform");
			}
			if (c == 'I')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right1.png", "EndPlatform");
			}
			if (c == 'U')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left3.png", "EndPlatform");
			}

			if (c == 'Y')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle3.png", "platform");
			}

			if (c == 'T')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right3.png", "EndPlatform");
			}

			if (c == 'u')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left4.png", "EndPlatform");
			}

			if (c == 'y')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle4.png", "platform");
			}

			if (c == 't')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right4.png", "EndPlatform");
			}

			if (c == 'p')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left6.png", "EndPlatform");
			}

			if (c == 'o')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle6.png", "platform");
			}

			if (c == 'i')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right6.png", "EndPlatform");
			}

			if (c == 'l')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/left5.png", "EndPlatform");
			}

			if (c == 'm')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/middle5.png", "platform");
			}

			if (c == 'r')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/right5.png", "EndPlatform");
			}

			if (c == 'C')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Coin/coin.png", "coin");
			}

			if (c == 'c')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/bottle.png", "bottle");
			}

			if (c == 'd')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE * 3, SCALE * 3 };
				ObstacleManager::addObstacle(temp, world, "Assets/Platform/d001.png", "door");
			}

			if (c == 'E') //FlyingEnemy
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addEnemy(temp, true, world, "flyingEnemy");
			}

			if (c == 'e') //GroundEnemy
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addEnemy(temp, false, world, "Enemy");
			}
		}
	}
}

vector<string> Level::LoadFromTextFile(string name)
{

	vector<string > mystringvector;
	ifstream myfile;
	myfile.open(name);
	string c = "";
	while (myfile >> c)
	{
		mystringvector.push_back(c);
	}

	myfile.close();
	return mystringvector;

	return std::vector<std::string>();
}