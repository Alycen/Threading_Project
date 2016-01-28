#ifndef POT_H
#define POT_H

#include <iostream>
#include <stdio.h>

#include <windows.h>

#include <random>
#include <string>
#include <cmath>

#include <fstream>

#include <SDL.h>
#include "Sprite.h"
#include "Renderer.h"

static class Pot
{
private:
	SDL_Rect rect;
	Sprite* m_sprite;
	int spriteOffset;

public:

	Pot();
	~Pot()
	{
		delete m_sprite;
	}
	void Init(SDL_Rect pos, std::string path);
	void Draw(int offset);
	SDL_Rect gSpriteClips[8];
	int frame;
	void NextPotImage();
	void CheckScore(int score);


};
#endif