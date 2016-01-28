#include "Pot.h"
#include <SDL_image.h>

Pot::Pot() {
}
void Pot::Init(SDL_Rect pos, std::string path) {
	rect = pos;
	SDL_Rect tempSRC{ 0,0,80,80 };
	m_sprite = new Sprite();
	m_sprite->Init(path, pos, tempSRC);

	//Set sprite clips
	gSpriteClips[0].x = 80;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 80;
	gSpriteClips[0].h = 80;

	gSpriteClips[1].x = 160;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 80;
	gSpriteClips[1].h = 80;

	gSpriteClips[2].x = 240;
	gSpriteClips[2].y = 0;
	gSpriteClips[2].w = 80;
	gSpriteClips[2].h = 80;

	gSpriteClips[3].x = 320;
	gSpriteClips[3].y = 0;
	gSpriteClips[3].w = 80;
	gSpriteClips[3].h = 80;

	gSpriteClips[4].x = 400;
	gSpriteClips[4].y = 0;
	gSpriteClips[4].w = 80;
	gSpriteClips[4].h = 80;

	gSpriteClips[5].x = 480;
	gSpriteClips[5].y = 0;
	gSpriteClips[5].w = 80;
	gSpriteClips[5].h = 80;

	gSpriteClips[6].x = 560;
	gSpriteClips[6].y = 0;
	gSpriteClips[6].w = 80;
	gSpriteClips[6].h = 80;

	gSpriteClips[7].x = 640;
	gSpriteClips[7].y = 0;
	gSpriteClips[7].w = 80;
	gSpriteClips[7].h = 80;



	frame = 0;
}
void Pot::Draw(int offset) {
	m_sprite->SetPosition(offset + 550, m_sprite->GetY());
	m_sprite->Draw();
}

void Pot::CheckScore(int score)
{
	if (score > 10 && score < 40)
	{
		m_sprite->SetSourceRect(gSpriteClips[1]);
	}

	else if (score > 40 && score < 60)
	{
		m_sprite->SetSourceRect(gSpriteClips[2]);
	}

	else if (score > 60 && score < 80)
	{
		m_sprite->SetSourceRect(gSpriteClips[3]);
	}


	else if (score > 80 && score < 100)
	{
		m_sprite->SetSourceRect(gSpriteClips[4]);
	}

	else if (score > 100 && score < 120)
	{
		m_sprite->SetSourceRect(gSpriteClips[5]);
	}

	else if (score > 120 && score < 150)
	{
		m_sprite->SetSourceRect(gSpriteClips[6]);
	}

	else if (score > 150)
	{
		m_sprite->SetSourceRect(gSpriteClips[7]);
	}


}
