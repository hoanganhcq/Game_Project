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
#include "GameOverScreen.h"
#include "Menu.h"
#include "PauseContainer.h"
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
	Button muteButton, unmuteButton;
	//


	SDL_Window* window;
	SDL_Event event = {};
	SDL_Renderer* renderer;

	Mix_Music* bgMusic = NULL;
	Mix_Chunk* button_pressed_sound = NULL;
	Mix_Chunk* enemy_is_hitSound = NULL;
	enum MusicState { NONE, MENU_MUSIC, GAME_MUSIC, GAMEOVER_MUSIC };
	MusicState currentMusic = NONE;

	bool Mute = false;


	TTF_Font* pauseFont = NULL;

	int score = 0;
	std::vector<int> highScores;
	TTF_Font* scoreFont = NULL;
	SDL_Texture* scoreTextTexture = NULL;
	SDL_Rect scoreTextRect;
	//bool scoreNeedsUpdade = true;

//Game Over Screen
	GameOverScreen* gameOverScreen = NULL;
	bool restartRequested = false;
	bool exitRequested = false;

//Menu
	Menu* menu = NULL;
	bool inMenu = true;
	bool playRequested = false;
	bool quitRequested = false;

// Pause Container
	PauseContainer* pauseContainer = NULL;
	bool resumeRequested = false;
	bool pauseExitRequested = false;
public:
	GameLoop();
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