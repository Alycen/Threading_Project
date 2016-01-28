#include "Player.h"
#include <SDL_image.h>

static const float SCALE = 30.f;

// Constructor
Player::Player() :CollisionResponder()
{

}

void Player::Init(SDL_Rect pRect, b2World *pWorld)
{

	respawnPlayer = false;

	lastLeft = false;
	health = 5;
	direction = 0;
	initPos = pRect;
	myRect = pRect;
	//spriteOffset = 32;
	//myBodyDef.type = b2_staticBody;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set((myRect.x + myRect.w*0.5f) / SCALE, (myRect.y + myRect.h*0.5f) / SCALE);
	myBody = pWorld->CreateBody(&myBodyDef);
	myBody->SetGravityScale(3.0f);
	myBody->SetFixedRotation(true);
	myBody->SetSleepingAllowed(false);
	myBody->SetUserData(this);

	//myBody->SetLinearDamping(1);

	myShape.SetAsBox((pRect.w / 2) / SCALE, (pRect.h / 2) / SCALE);

	myBodyFixtureDef.shape = &myShape;
	myBodyFixtureDef.friction = 0.7;
	myBodyFixtureDef.userData = "player";
	myBody->CreateFixture(&myBodyFixtureDef);

	source = { 0, 0, 60, 65 };

	playerStandStillRightSprite.Init("Assets/Player/IdleRight.png", pRect, source);
	playerStandStillRightSprite.SetOffset(30, 32);

	playerStandStillLeftSprite.Init("Assets/Player/IdleLeft.png", pRect, source);
	playerStandStillLeftSprite.SetOffset(30, 32);

	playerLeftSprite.Init("Assets/Player/playerLeft.png", pRect, source);
	playerLeftSprite.SetOffset(30, 32);

	playerRightSprite.Init("Assets/Player/playerRight.png", pRect, source);
	playerRightSprite.SetOffset(30, 32);

	playerJumpRight.Init("Assets/Player/JumpRight.png", pRect, source);
	playerJumpRight.SetOffset(30, 32);

	playerJumpLeft.Init("Assets/Player/JumpLeft.png", pRect, source);
	playerJumpLeft.SetOffset(30, 32);

	myBodyDef.userData = this;

	canJump = true;
	//Set sprite clips
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 60;
	gSpriteClips[0].h = 65;

	gSpriteClips[1].x = 60;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 60;
	gSpriteClips[1].h = 65;

	gSpriteClips[2].x = 120;
	gSpriteClips[2].y = 0;
	gSpriteClips[2].w = 60;
	gSpriteClips[2].h = 65;

	gSpriteClips[3].x = 180;
	gSpriteClips[3].y = 0;
	gSpriteClips[3].w = 60;
	gSpriteClips[3].h = 65;

	gSpriteClips[4].x = 240;
	gSpriteClips[4].y = 0;
	gSpriteClips[4].w = 60;
	gSpriteClips[4].h = 65;

	gSpriteClips[5].x = 300;
	gSpriteClips[5].y = 0;
	gSpriteClips[5].w = 60;
	gSpriteClips[5].h = 65;

	gSpriteClips[6].x = 360;
	gSpriteClips[6].y = 0;
	gSpriteClips[6].w = 60;
	gSpriteClips[6].h = 65;

	gSpriteClips[7].x = 420;
	gSpriteClips[7].y = 0;
	gSpriteClips[7].w = 60;
	gSpriteClips[7].h = 65;

	gSpriteClips[8].x = 480;
	gSpriteClips[8].y = 0;
	gSpriteClips[8].w = 60;
	gSpriteClips[8].h = 65;

	gSpriteClips[9].x = 540;
	gSpriteClips[9].y = 0;
	gSpriteClips[9].w = 60;
	gSpriteClips[9].h = 65;

	gSpriteClips[10].x = 600;
	gSpriteClips[10].y = 0;
	gSpriteClips[10].w = 60;
	gSpriteClips[10].h = 65;


	frame = 0;

	score = 0;
}

//Doesnt work... Oh well... Who really cares?
void Player::Animate()
{
	//Current animation frame


	//Render current frame
	SDL_Rect currentClip = gSpriteClips[frame / 3];

	//stand still
	//if (direction == 0)
	//{
	//	playerStandStillLeftSprite.SetSourceRect(currentClip);
	//}

	//Left
	if (direction == 1)
	{
		playerLeftSprite.SetSourceRect(currentClip);
	}

	//Right
	else if (direction == 2)
	{
		playerRightSprite.SetSourceRect(currentClip);
	}

	//else if (direction == 4)
	//{
	//	playerJumpRight.SetSourceRect(currentClip);
	//}

	//else if (direction == 5)
	//{
	//	playerJumpLeft.SetSourceRect(currentClip);
	//}

	++frame;


	if (frame / 3 > 10)
	{
		frame = 0;
	}

}

bool Player::Update()
{

	if (respawnPlayer == true) {
		respawnPlayer = false;
		myBody->SetTransform(b2Vec2(200 / SCALE, 200 / SCALE), 0);
	}

	myRect.x = myBody->GetPosition().x * SCALE;
	myRect.y = myBody->GetPosition().y * SCALE;

	// Can jump if y-velocity is 0
	if (myBody->GetLinearVelocity().y == 0)
	{
		canJump = true;
		myBodyFixtureDef.friction = 100;
	}
	else
	{
		canJump = false;
		myBodyFixtureDef.friction = 0;
	}

	if (direction == 0)
	{
		playerStandStillLeftSprite.SetPosition(myBody->GetPosition().x * SCALE, myBody->GetPosition().y * SCALE);
	}

	else if (direction == 3)
	{
		playerStandStillRightSprite.SetPosition(myBody->GetPosition().x * SCALE, myBody->GetPosition().y * SCALE);
	}

	//Left
	else if (direction == 1)
	{
		playerLeftSprite.SetPosition(myBody->GetPosition().x * SCALE, myBody->GetPosition().y * SCALE);
	}

	//Right
	else if (direction == 2)
	{
		playerRightSprite.SetPosition(myBody->GetPosition().x * SCALE, myBody->GetPosition().y * SCALE);
	}

	else if (direction == 4)
	{
		playerJumpRight.SetPosition(myBody->GetPosition().x * SCALE, myBody->GetPosition().y * SCALE);
	}

	else if (direction == 5)
	{
		playerJumpLeft.SetPosition(myBody->GetPosition().x * SCALE, myBody->GetPosition().y * SCALE);
	}


	return true;
}

void Player::Move(InputHandler & input)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_LSHIFT]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x - 0.25, myBody->GetPosition().y), 0);
		if (myBody->GetLinearVelocity().y == 0)
		{
			direction = 1;
		}
		lastLeft = true;
	}

	if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_LSHIFT]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x - 0.40, myBody->GetPosition().y), 0);
		if (myBody->GetLinearVelocity().y == 0)
		{
			direction = 1;
		}
		lastLeft = true;
	}

	if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_LSHIFT]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x + 0.25, myBody->GetPosition().y), 0);
		//myBody->ApplyLinearImpulse(b2Vec2(0.7f, 0), myBody->GetWorldCenter(), false);
		if (myBody->GetLinearVelocity().y == 0)
		{
			direction = 2;
		}
		lastLeft = false;
	}

	if (keys[SDL_SCANCODE_D] && keys[SDL_SCANCODE_LSHIFT]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x + 0.40, myBody->GetPosition().y), 0);
		if (myBody->GetLinearVelocity().y == 0)
		{
			direction = 2;
		}
		lastLeft = false;
	}

	if (keys[SDL_SCANCODE_SPACE]) {
		if (canJump == true)
		{
			myBody->ApplyLinearImpulse(b2Vec2(0, -18), b2Vec2(0, 0), false);

			if (myBody->GetLinearVelocity().y != 0)
			{
				if (!keys[SDL_SCANCODE_A])
				{
					direction = 4;
					lastLeft = true;
				}
				if (!keys[SDL_SCANCODE_D])
				{
					direction = 5;
					lastLeft = false;
				}
			}
		}
	}

	if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D])
	{
		if (myBody->GetLinearVelocity().y != 0)
		{
			if (myBody->GetLinearVelocity().x >= 0)
			{
				direction = 4;
			}
			else if (myBody->GetLinearVelocity().x <= 0)
			{
				direction = 5;
			}
		}
		else
		{
			if (lastLeft == true)
			{
				direction = 0;
			}
			else
			{
				direction = 3;
			}
		}
	}


}

void Player::Draw()
{
	if (direction == 0)
	{
		playerStandStillLeftSprite.Draw();
	}

	if (direction == 3)
	{
		playerStandStillRightSprite.Draw();
	}

	//Left
	else if (direction == 1)
	{
		playerLeftSprite.Draw();
	}

	//Right
	else if (direction == 2)
	{
		playerRightSprite.Draw();
	}

	else if (direction == 4)
	{
		playerJumpRight.Draw();
	}

	else if (direction == 5)
	{
		playerJumpLeft.Draw();
	}

	Animate();
}

void Player::Respawn() {
	
	//myBody->SetTransform(b2Vec2(initPos.x, initPos.y),0);
}

void Player::Add_SubHealth(int amount) {
	health += amount;
}

SDL_Rect Player::getRectangle()
{
	return myRect;
}

b2Body *Player::getBody()
{
	return myBody;
}

void Player::onBeginContact(CollisionResponder* other) {
	std::cout << "enemy Collide begin" << std::endl;
	printf("++contact++");
}

void Player::onEndContact(CollisionResponder* other) {
	std::cout << "enemy Collide end" << std::endl;
	printf("++contact++");
}

int Player::GetScore()
{
	return score;
}

b2Vec2 Player::getPos() {
	return b2Vec2(myRect.x, myRect.y);
}
