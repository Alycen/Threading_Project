#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#undef main
#include "Box2D\Box2D.h"
#include "Button.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "ObstacleManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Door.h"
#include "MyContactListener.h"
#include "FollowEnemy.h"
#include "Leaderboard.h"
#include "Pot.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1248;			//SDL
const int SCREEN_HEIGHT = 704;			//SDL

										//320										//gamestates
const int MENU = 0, PLAY = 1, PAUSE = 2, GAMEOVER = 3, SCORE = 4;
int gameState;

InputHandler inputHandler = InputHandler();
Sprite* backGroundImage;
Sprite* scoreBoardImage;
Sprite* skyBackGround;
Sprite* cloud1;
Sprite* cloud2;
Sprite* cloud3;
Button playButton;
Button playButton1;
Button scoreButton;
Button exitButton;
MyContactListener myContactListenerInstance;
Leaderboard leaderboard;
Pot pot;


// Player
SDL_Rect myRect{ 200, 200, 60, 65 };
Player player;

SDL_Rect potRect{ 500, 0, 80, 80 };


//box2d stuff
const int SCALE = 32;
b2Vec2 gravity(0.0f, 9.8f);

// Construct a world object, which will hold and simulate the rigid bodies.
b2World *world = new b2World(gravity);
// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
float32 timeStep = 1.0f / 60.0f;
int32 velocityIterations = 6;
int32 positionIterations = 2;
int playerX;


//methods
void Init();
void DrawGame();
void DrawMenu();
void DrawLeaderboard();
void UpdateGame();
void UpdateLeaderboard(SDL_Event e);
bool UpdateMenu(SDL_Event e);
void Reset();
void ClearPointers();
void CheckDoorCollisions();
void SetPlayerPosition();

bool wentThroughTopDoor, wentThroughBottomDoor, wentThroughRightDoor, wentThroughLeftDoor;
int main()
{
	//B2_NOT_USED(argc);
	//B2_NOT_USED(argv);
	gameState = MENU;
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	const float box2D_timestep = 1.0f / 60.0f;
	const int vel_iterations = 6;
	const int pos_iterations = 2;

	Mix_Music *music = NULL;
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1;
	music = Mix_LoadMUS(("Assets/background.wav"));
	Mix_PlayMusic(music, -1);


	//SDL
#pragma region SDL STUFF
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create Renderer for the Window
			if (!Renderer::GetInstance()->Init(window, SCREEN_WIDTH, SCREEN_HEIGHT))
			{
				return 0;
			}

			bool quit = false;
			Init();




			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) {
					if (inputHandler.CheckInput(SDLK_ESCAPE, e)) {
						quit = true;
					}
				}

				//controls gameState added in game menu feature
				switch (gameState)
				{
				case MENU:
					//updateMenu
					quit = UpdateMenu(e);
					//draw menu
					DrawMenu();

					break;
				case PLAY:
					UpdateGame();
					DrawGame();
					if (player.getBody()->GetPosition().x * SCALE > 2480)
					{
						scoreBoardImage->SetPosition(2022, 0);
						gameState = SCORE;
					}
					world->Step(box2D_timestep, vel_iterations, pos_iterations);
					break;

				case SCORE:
					UpdateLeaderboard(e);
					DrawLeaderboard();
					break;
				}//end switch

				 // Escape button
				if (inputHandler.CheckInput(SDLK_ESCAPE, e))//::GetInstance()->isKeyPressed(SDLK_ESCAPE))
				{
					quit = true;
				}

			}//end while wuit
		}//end else
	}//end else

	ClearPointers();
	return 0;
}

void Init()
{
	wentThroughBottomDoor = wentThroughLeftDoor = wentThroughRightDoor = wentThroughTopDoor = false;
	player.Init(myRect, world);
	pot.Init(potRect, "Assets/Pot/pot.png");
	Level::LoadLevel("Level1.txt", world);
	gameState = MENU;
	backGroundImage = new Sprite();
	scoreBoardImage = new Sprite();
	skyBackGround = new Sprite();
	cloud1 = new Sprite();
	cloud2 = new Sprite();
	cloud3 = new Sprite();
	SDL_Rect destination = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Source = { 0, 0, 1240, 720 };
	SDL_Rect destination1 = { 0, -200, SCREEN_WIDTH, SCREEN_HEIGHT };
	backGroundImage->Init("Assets/menu.png", destination1, Source);
	scoreBoardImage->Init("Assets/BG/scoreback.png", destination, Source);
	skyBackGround->Init("Assets/BG/bg_day.png", destination, Source);

	destination = { SCREEN_WIDTH / 2 - 550, SCREEN_HEIGHT / 4 - 145, 323, 118 };
	cloud1->Init("Assets/cloud1.png", destination, Source);
	destination = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 4 - 65, 323, 118 };
	cloud2->Init("Assets/cloud2.png", destination, Source);
	destination = { SCREEN_WIDTH / 2 + 375, SCREEN_HEIGHT / 4 - 150, 323, 118 };
	cloud3->Init("Assets/cloud3.png", destination, Source);


	destination = { 100, 420, 600, 160 };
	scoreButton.Init(destination, "Assets/ScoreButton.png");

	destination = { 100,560, 600, 160 };
	exitButton.Init(destination, "Assets/ExitButton.png");

	destination = { 100, 280, 600, 160 };
	playButton.Init(destination, "Assets/PlayButton.png");

	destination = { 60, 440, 600, 160 };
	playButton1.Init(destination, "Assets/PlayButton.png");

	world->SetContactListener(&myContactListenerInstance);
	leaderboard = Leaderboard();

}
void DrawGame()
{
	Renderer::GetInstance()->ClearRenderer();

	/*Call Darw on objects here*/
	skyBackGround->DrawBackground(player.getRectangle());
	cloud1->DrawCloud();
	cloud2->DrawCloud();
	cloud3->DrawCloud();
	skyBackGround->Draw();
	

	player.Draw();
	pot.Draw(Renderer::GetInstance()->CameraXOffSet);

	ObstacleManager::GetInstance()->Draw();

	Renderer::GetInstance()->RenderScreen();
}
void DrawMenu()
{
	Renderer::GetInstance()->ClearRenderer();
	/*Call Darw on objects here*/
	backGroundImage->Draw();


	playButton.Draw();
	scoreButton.Draw();
	exitButton.Draw();

	Renderer::GetInstance()->RenderScreen();
}
void DrawLeaderboard()
{
	Renderer::GetInstance()->ClearRenderer();

	/*Call Darw on objects here*/
	scoreBoardImage->Draw();
	playButton1.Draw();

	Renderer::GetInstance()->RenderScreen();
}

bool UpdateMenu(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		//If the left mouse button was pressed
		if (e.button.button == SDL_BUTTON_LEFT) {
			//Get the mouse offsets
			int mouse_x = e.button.x;
			int mouse_y = e.button.y;

			std::cout << "Mouse Button 1 (left) is pressed. x = " << mouse_x << ", y = " << mouse_y << std::endl;
			if (playButton.IsClicked(mouse_x, mouse_y)) {
				gameState = PLAY;
			}
			if (scoreButton.IsClicked(mouse_x, mouse_y)) {
				gameState = SCORE;
			}
			if (exitButton.IsClicked(mouse_x, mouse_y)) {
				return true;
			}
		}
	}
	return false;
}
void UpdateLeaderboard(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		//If the left mouse button was pressed
		if (e.button.button == SDL_BUTTON_LEFT) {
			//Get the mouse offsets
			int mouse_x = e.button.x;
			int mouse_y = e.button.y;
			//SDL_Log("Mouse Button 1 (left) is pressed. x = " + x );
			std::cout << "Mouse Button 1 (left) is pressed. x = " << mouse_x << ", y = " << mouse_y << std::endl;
			if (playButton1.IsClicked(mouse_x, mouse_y)) {
				gameState = PLAY;
			}
		}
	}
}
void UpdateGame()
{
	playerX = player.getPos().x;
	player.Move(inputHandler);
	player.Update();
	pot.CheckScore(player.score);
	Renderer::GetInstance()->updateCameraPosition(playerX);
	//cout << "Player X Position = " + player.getRectangle().x << endl;
	//cout << "Player Y Position = " + player.getRectangle().y << endl;
	//cout << "Door X Position = " + door.GetTopDoorRect().x << endl;
	//cout << "Door Y Position = " + door.GetTopDoorRect().y << endl;
	CheckDoorCollisions();
	world->Step(timeStep, velocityIterations, positionIterations);
}
void Reset()
{

}
void ClearPointers()
{
	delete world;
	delete backGroundImage;
	delete skyBackGround;
}

void CheckDoorCollisions()
{
}

void SetPlayerPosition()
{
}
