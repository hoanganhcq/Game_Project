#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Background.h"
#include "Character.h"
#include "Tile.h"
#include "CollisionManager.h"
#include "Projectile.h"
#include "EnemyAI.h"
#include "Button.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class GameLoop
{
private:

	Background background, _background;
	Character player;
	Projectile energy_attack_1, enemyProjectile;

// Enemy
	Character enemy;
	Projectile enemy_projectile;
	EnemyAI enemyAI;
//

	Tile curr_map, next_map;
	std::vector<Tile> tileMapList;
	

	const int WIDTH = 1800;
	const int HEIGHT = 1000;

	bool GameState;
	bool Pause = false;
	bool GameOver = false;
	int waitForDeath_timer = 0;

//Button
	Button pauseButton, resumePlayingButton;
//

	SDL_Window* window;
	SDL_Event event = {};
	SDL_Renderer* renderer;

	Mix_Music* bgMusic;
	
	TTF_Font* pauseFont = NULL;
	SDL_Texture* pauseTextTexture = NULL;
	SDL_Rect pauseTextRect;

	int score = 0;
	std::vector<int> highScores;
	TTF_Font* scoreFont = NULL;
	SDL_Texture* scoreTextTexture = NULL;
	SDL_Rect scoreTextRect;
	//bool scoreNeedsUpdade = true;
	SDL_Texture* gameOverTextTexture = NULL;
	SDL_Rect gameOverTextRect;
public:
	GameLoop();
	int currIndex = 0;
	bool getGameState();
	void Update();
	void Initialize();
	void Event();
	void Render();
	void Clear();
	void ResetGame();

	int deathTimer = 0;
	bool waitingForRevive = false;
};