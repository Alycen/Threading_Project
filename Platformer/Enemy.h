#ifndef _ENEMY_
#define _ENEMY_
#include "Obstacle.h"

class Enemy : public Obstacle {
public:
	Enemy();
	Enemy(SDL_Rect rect, bool flying, b2World* world, void * name);
	~Enemy();

	b2Body* m_Body;
	void Update();
	void Move();
	void Swap();
	void Die();
	void Draw();
private:
	b2BodyDef mBodyDef;
	b2FixtureDef mBodyFixtureDef;
	Sprite sprite, gleft, fleft, gright, fright;
	b2PolygonShape mShape;
	SDL_Texture* mTexture;
	//end of platform Sensors
	SDL_Rect gSpriteClips;
	SDL_Rect mRect;
	SDL_Rect source;
	int direction;
	float speed = 0.05f;
	bool flying = false;
	bool alive = true;
	float maxLeft;
	float maxRight;
};

#endif