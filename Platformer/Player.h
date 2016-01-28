#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> 
#include "sdl.h"
#include "Box2D\Box2D.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "CollisionResponder.h"

class Player : public CollisionResponder
{
public:
	Player();
	SDL_Rect gSpriteClips[11];
	void Init(SDL_Rect, b2World*);
	bool Update();
	void Draw();
	void Move(InputHandler & input);
	void Animate();
	void Respawn();
	void Add_SubHealth(int amount);
	int frame;
	SDL_Rect getRectangle();
	b2Body* getBody();
	b2Vec2 getPos();
	int score;
	//needed to override the contact classes in the collision reponder
	virtual void onBeginContact(CollisionResponder* other) override;
	virtual void onEndContact(CollisionResponder* other) override;
	int GetScore();

	bool respawnPlayer;
private:
	int health;
	SDL_Rect initPos;
	SDL_Rect myRect;
	SDL_Rect source;
	int spriteOffset;
	b2BodyDef myBodyDef;
	b2Body* myBody;
	b2PolygonShape myShape;
	b2FixtureDef myBodyFixtureDef;

	Sprite playerStandStillRightSprite, playerStandStillLeftSprite, playerLeftSprite, playerRightSprite, playerJumpRight, playerJumpLeft;
	int direction;	//1 is left // 2 is right // 0 is idle // 3 could be jumping..
	bool canJump;
	bool lastLeft;
};

#endif