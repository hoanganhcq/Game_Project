#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Background.h"
#include "Character.h"
#include <iostream>

class GameLoop
{
private:

	Background background_1, background_2;
	Character player;

	const int WIDTH = 1800;
	const int HEIGHT = 1080;

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