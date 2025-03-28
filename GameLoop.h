#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Background.h"
#include "Character.h"
#include "Tile.h"
#include "CollisionManager.h"
#include <iostream>
#include <vector>

class GameLoop
{
private:

	Background background;
	Character player;

	Tile curr_map, next_map;//
	std::vector<Tile> tileMapList;
	

	const int WIDTH = 1800;
	const int HEIGHT = 1000;

	bool GameState;
	SDL_Window* window;
	SDL_Event event = {};
	SDL_Renderer* renderer;
public:
	GameLoop();
	int currIndex = 0;
	bool getGameState();
	void Update();
	void Initialize();
	void Event();
	void Render();
	void Clear();
};