#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Background.h"
#include "Character.h"
#include "Tile.h"
#include "CollisionManager.h"
#include <iostream>

class GameLoop
{
private:

	Background background;
	Character player;
	Tile tiles;//

	const int WIDTH = 1800;
	const int HEIGHT = 1000;

	bool GameState;
	SDL_Window* window;
	SDL_Event event = {};
	SDL_Renderer* renderer;
public:
	GameLoop();
	bool getGameState();
	void Update();
	void Initialize();
	void Event();
	void Render();
	void Clear();
};