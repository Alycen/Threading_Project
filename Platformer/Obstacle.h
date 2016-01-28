#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream> 
#include "sdl.h"
#include "Box2D\Box2D.h"
//#include "KeyboardInputs.h"
#include "Renderer.h"
#include "Sprite.h"
#include <string>
using namespace std;

class Obstacle
{
public:
	Obstacle();
	Obstacle(SDL_Rect, b2World*, string, void *);
	b2Body* myBody;
	Obstacle(SDL_Rect, string);
	// Public member functions
	void Draw();
	void Remove();
	bool destroyed;
	SDL_Rect gSpriteClips[8];
	int frame;
	void Animate();
	void AnimationFrames();
	void CreateThread();
private:
	b2BodyDef myBodyDef;
	b2FixtureDef myBodyFixtureDef;
	Sprite sprite;
	b2PolygonShape myShape;
	SDL_Texture* myTexture;
	SDL_Rect myRect;
	void * myName;

	SDL_Thread* AnimationThread;
};

#endif#pragma once



