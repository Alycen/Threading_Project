#include "Obstacle.h"
#include "Renderer.h"
#include <SDL_image.h>
#include "ThreadingMutex.h"

static const float SCALE = 30.f;

Obstacle::Obstacle()
{

}



int AnimationProcess(void *data) {
	/*
	while (static_cast<Obstacle*>(data)->destroyed==false) {
		if (SDL_LockMutex (mtx) != 0) {
			std::cout << "Queued / Waiting" << std::endl;
		}
		else {
			std::cout << "Locked (Critical Section). Thread :" << std::endl << (int)SDL_ThreadID() << std::endl;
			static_cast<Obstacle*>(data)->Animate();
			if (SDL_UnlockMutex(mtx) != 0) {
				std::cout << "Nothing in Queue" << std::endl;
			}
			std::cout << "Unlocked" << std::endl;
			SDL_Delay(10);
		}
	}
	return 0;*/
	while (static_cast<Obstacle*>(data)->destroyed == false) {
		SDL_Delay(1000);
		SDL_SemWait(sem);
		cout << "Locking Semaphore" << endl;
		SDL_Delay(100);
		static_cast<Obstacle*>(data)->Animate();
		cout << "Obstacle::Animate()" << endl;
		SDL_Delay(1000);
		SDL_SemPost(sem);
		cout << "Unlocking Semphore" << endl;
		SDL_Delay(100);
	}
	return 0;
}

void Obstacle::CreateThread() {
	AnimationThread = SDL_CreateThread(AnimationProcess, "Animation Thread", (void*)this);
}

void Obstacle::Animate()
{
	//Render current frame
	SDL_Rect currentClip = gSpriteClips[frame / 7];
	++frame;


	sprite.SetSourceRect(currentClip);

	if (frame / 7 > 7)
	{
		frame = 0;
	}
}

Obstacle::Obstacle(SDL_Rect pRect, b2World *wWorld, string path, void * name)
{

	destroyed = false;

	myRect = pRect;

	myName = name;

	// Define the ground body.
	myBodyDef.position.Set((pRect.x + pRect.w / 2 - 17) / SCALE, (pRect.y + pRect.h / 2 - 15) / SCALE);
	if (name == "coin")
	{
		myBodyDef.type = b2_dynamicBody;
		myBodyFixtureDef.isSensor = true;

	}
	else
	{
		myBodyDef.type = b2_staticBody;
	}

	if (name == "coin")
	{
		AnimationFrames();
		// Define the ground box shape.
		// The extents are the half-widths of the box.
		myShape.SetAsBox((pRect.w / 2 - 10) / SCALE, (pRect.h / 2) / SCALE);
		myBodyFixtureDef.shape = &myShape;
		myBodyFixtureDef.userData = name;

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		myBody = wWorld->CreateBody(&myBodyDef);
		myBody->SetGravityScale(0);
		SDL_Rect source = { 0,0,32,32 };

		// Add the ground fixture to the ground body.
		myBody->CreateFixture(&myBodyFixtureDef);
		myBody->SetUserData(this);
		myBody->SetFixedRotation(true);
		sprite.Init(path, pRect, source);
		sprite.SetOffset(16, 16.0f);
	}

	else if (name == "door")
	{
		// Define the ground box shape.
		// The extents are the half-widths of the box.
		myShape.SetAsBox((pRect.w / 2 - 10) / SCALE, (pRect.h / 2) / SCALE);
		myBodyFixtureDef.shape = &myShape;
		myBodyFixtureDef.userData = name;

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		myBody = wWorld->CreateBody(&myBodyDef);
		myBody->SetGravityScale(0);
		SDL_Rect source = { 0,0,80,80 };

		// Add the ground fixture to the ground body.
		myBody->CreateFixture(&myBodyFixtureDef);
		myBody->SetUserData(this);
		myBody->SetFixedRotation(true);
		sprite.Init(path, pRect, source);
		sprite.SetOffset(40, 40);
	}

	else
	{
		// Define the ground box shape.
		// The extents are the half-widths of the box.
		myShape.SetAsBox((pRect.w / 2 - 10) / SCALE, (pRect.h / 2) / SCALE);
		myBodyFixtureDef.shape = &myShape;
		myBodyFixtureDef.userData = name;

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		myBody = wWorld->CreateBody(&myBodyDef);
		myBody->SetGravityScale(0);
		SDL_Rect source = { 0,0,40,51 };

		// Add the ground fixture to the ground body.
		myBody->CreateFixture(&myBodyFixtureDef);
		myBody->SetUserData(this);
		myBody->SetFixedRotation(true);
		sprite.Init(path, pRect, source);
		sprite.SetOffset(20, 25.5f);
	}
}

Obstacle::Obstacle(SDL_Rect pRect, string path)
{
	myRect = pRect;
	SDL_Rect source = { 0,0,40,51 };

	sprite.Init(path, pRect, source);
	sprite.SetOffset(20, 25.5f);
}

void Obstacle::AnimationFrames()
{
	//Set sprite clips
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 32;
	gSpriteClips[0].h = 32;

	gSpriteClips[1].x = 32;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 32;
	gSpriteClips[1].h = 32;

	gSpriteClips[2].x = 64;
	gSpriteClips[2].y = 0;
	gSpriteClips[2].w = 32;
	gSpriteClips[2].h = 32;

	gSpriteClips[3].x = 96;
	gSpriteClips[3].y = 0;
	gSpriteClips[3].w = 32;
	gSpriteClips[3].h = 32;

	gSpriteClips[4].x = 128;
	gSpriteClips[4].y = 0;
	gSpriteClips[4].w = 32;
	gSpriteClips[4].h = 32;

	gSpriteClips[5].x = 160;
	gSpriteClips[5].y = 0;
	gSpriteClips[5].w = 32;
	gSpriteClips[5].h = 32;

	gSpriteClips[6].x = 192;
	gSpriteClips[6].y = 0;
	gSpriteClips[6].w = 32;
	gSpriteClips[6].h = 32;

	gSpriteClips[7].x = 224;
	gSpriteClips[7].y = 0;
	gSpriteClips[7].w = 32;
	gSpriteClips[7].h = 32;

	frame = 0;
}

void Obstacle::Draw()
{
	if (myName == "coin")
	{
		Animate();
		sprite.SetPosition((myBody->GetPosition().x * SCALE), myBody->GetPosition().y * SCALE);
		if (sprite.GetY() < -100)
		{
			destroyed = true;
			myBody->SetLinearVelocity(b2Vec2(0, 0));
			myBody->SetActive(false);
			myBody->SetAwake(false);
		}
	}
	sprite.Draw();
}

void Obstacle::Remove()
{
	myBody->SetLinearVelocity(b2Vec2(15, -15));
}