#include "GameLoop.h"
using namespace std;
GameLoop::GameLoop()
{
	window = NULL;
	renderer = NULL;
	GameState = false;

	background_1.setSrc(0, 0, 1050, 1050);
	background_1.setDest(0, 0, 1080, 1080);
	background_2.setSrc(0, 0, 1050, 1050);
	background_2.setDest(1080, 0, 1080, 1080);

	player.setSrc(0, 0, 50, 50);
	player.setDest(200, 200, 50, 50);
}

bool GameLoop::getGameState()
{
	return GameState;
}

void GameLoop::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			cout << "Created Renderer" << endl;
			GameState = true;
			background_1.CreateTexture("assets/image/background.png", renderer);
			background_2.CreateTexture("assets/image/background.png", renderer);
			player.CreateTexture("assets/image/player_test.png",renderer);
		}
		else cout << "Renderer was not created!" << endl;
	}
	else cout << "Window was not created :<" << endl;
}

void GameLoop::Event()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		GameState = false;
	}

	player.Movement(event);
}

void GameLoop::Update()
{
	background_1.BackgroundUpdate();

	player.PositionUpdate();
}

void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	background_1.GroundRender(renderer);
	background_2.GroundRender(renderer);
	player.Render(renderer);

	SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}