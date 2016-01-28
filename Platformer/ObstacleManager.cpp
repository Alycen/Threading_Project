#include "ObstacleManager.h"

bool ObstacleManager::instanceFlag = false;
ObstacleManager* ObstacleManager::instance = NULL;

std::vector<Obstacle *> ObstacleManager::obstacles(0);
std::vector<Obstacle *> ObstacleManager::floor(0);
std::vector<Enemy*> ObstacleManager::enemies(0);

void ObstacleManager::Init(b2World * pWorld, SDL_Renderer * gRenderer)
{
}

void ObstacleManager::Draw()
{
	CheckLife();
	for each  (Obstacle * obstacle in obstacles) {

		obstacle->Draw();
	}
	for each  (Obstacle * obstacle in floor) {

		obstacle->Draw();
	}

	for each (Enemy * enemy in enemies) {
		enemy->Draw();
		enemy->Update();
	}
}

void ObstacleManager::CheckLife()
{
	vector<Obstacle*>::iterator iter;
	vector<Obstacle*>::iterator endIter;

	iter = obstacles.begin();
	endIter = obstacles.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->destroyed == true)
		{
			if (obstacles.size() == 1)
			{
				//world->DestroyBody(obstacles.at(0)->myBody);
				obstacles.clear();
				break;
			}
			else
			{
				//world->DestroyBody((*iter)->myBody);
				iter = obstacles.erase(iter);
				iter = obstacles.begin();
				endIter = obstacles.end();
			}
		}
	}

}

void ObstacleManager::Update()
{
}

void ObstacleManager::Reset(SDL_Rect)
{
}

ObstacleManager * ObstacleManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ObstacleManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void ObstacleManager::addObstacle(SDL_Rect pRect, b2World * world, string path, void * name)
{
	if (name == "coin") {
		Obstacle* temp = new Obstacle(pRect, world, path, name);
		temp->CreateThread();
		obstacles.push_back(temp);
	}
	else
		obstacles.push_back(new Obstacle(pRect, world, path, name));
}
void ObstacleManager::addfloor(SDL_Rect pRect, string path)
{
	floor.push_back(new Obstacle(pRect, path));
}
void ObstacleManager::addEnemy(SDL_Rect pRect, bool type, b2World* world, void * name) {
	enemies.push_back(new Enemy(pRect, type, world, name));
}


void ObstacleManager::ResetRoom(b2World * world)
{
	for each  (Obstacle * obstacle in obstacles) {

		world->DestroyBody(obstacle->myBody);
	}

	floor.clear();
	obstacles.clear();
}