#include "GameLoop.h"
using namespace std;
GameLoop::GameLoop()
{
	window = NULL;
	renderer = NULL;
	GameState = false;

	background.setSrc(0, 0, 1800, 1000);
	background.setDest(0, 0, 1800, 1000);

	player.setSrc(0, 0, 100, 100);
	player.setDest(200, 200, 100, 100);
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
			background.CreateTexture("assets/image/background.png", renderer);
			player.setSpriteSheet(renderer);

			tiles.loadTileMap("tileset.txt");
			tiles.setupTiles();
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

	player.handleInput(event);
}

void GameLoop::Update()
{
	background.BackgroundUpdate();
	player.Update();
	CollisionManager::handleCollisions(player, tiles);
}

void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	background.GroundRender(renderer);
	tiles.Render(renderer);
	player.Render(renderer);

	SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}