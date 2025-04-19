#include "GameLoop.h"
#include <random>
using namespace std;

int getRandomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}


GameLoop::GameLoop()
	:enemyAI(enemy_projectile)
{
	window = NULL;
	renderer = NULL;
	GameState = false;


	background.setSrc(0, 0, 1800, 1000);
	background.setDest(0, 0, 1800, 1000);
	_background.setSrc(0, 0, 1800, 1000);
	_background.setDest(1800, 0, 1800, 1000);

	player.setPlayer();
	//player.setSrc(0, 0, 100, 100);
	player.setRect(200, 100, 100, 100);
	
	//enemy.setSrc(0, 0, 100, 100);
	enemy.setRect(1600, 50, 100, 100);
}

bool GameLoop::getGameState()
{
	return GameState;
}

void GameLoop::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
		/*GameState = false;*/
		return;
	}
	bgMusic = Mix_LoadMUS("assets/audio/bgMusic.mp3");
	Mix_PlayMusic(bgMusic, -1);
	Mix_VolumeMusic(64); // 0 -> 128


	if (TTF_Init() < 0)
	{
		std::cout << "SDL_ttf could not initialize! " << TTF_GetError() << std::endl;
	}


	if (window)
	{
		cout << "Created Window" << endl;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			GameState = true;
			background.CreateTexture("assets/image/game_background.png", renderer);
			_background.CreateTexture("assets/image/game_background.png", renderer); _background.offSetX = 1800;
			player.player_setSpriteSheet(renderer);
			player.player_setAudio();
			energy_attack_1.setSpriteSheet(renderer, "assets/image/energy_attack_1.png");
			enemy.enemy_setSpriteSheet(renderer);
			enemyProjectile.setSpriteSheet(renderer, "assets/image/projectile_monster.png");
			enemyProjectile.setSpeed(3);


			EnemyAI enemyAI(enemy_projectile);


			Tile tileMap_0, tileMap_1, tileMap_2, tileMap_3, tileMap_4, tileMap_5;
			tileMap_0.loadTileMap("tileSet/tileSet_0.txt"); tileMap_0.setupTiles(renderer);
			tileMap_1.loadTileMap("tileSet/tileSet_1.txt"); tileMap_1.setupTiles(renderer);
			tileMap_2.loadTileMap("tileSet/tileSet_2.txt"); tileMap_2.setupTiles(renderer);
			tileMap_3.loadTileMap("tileSet/tileSet_3.txt"); tileMap_3.setupTiles(renderer);
			tileMap_4.loadTileMap("tileSet/tileSet_4.txt"); tileMap_4.setupTiles(renderer);
			tileMap_5.loadTileMap("tileSet/tileSet_5.txt"); tileMap_5.setupTiles(renderer);
			tileMapList = { tileMap_1, tileMap_2, tileMap_3, tileMap_4, tileMap_5 };


			curr_map = tileMap_0;
			next_map = tileMapList[0];  next_map.offSetX = 1800; // mapWidth = 1800


			pauseFont = TTF_OpenFont("assets/truetype_font/WinkyRough-VariableFont_wght.ttf", 48);
			scoreFont = TTF_OpenFont("assets/truetype_font/PoetsenOne-Regular.ttf", 32);
			if (!pauseFont || !scoreFont)
			{
				std::cout << "Failed to load font! SDL_ttd Error: " << TTF_GetError() << std::endl;
			}
			else
			{
				SDL_Color textColor = { 255, 255, 255, 255 }; // white
				SDL_Surface* textSurface = TTF_RenderText_Solid(pauseFont, "Paused", textColor);
				if (textSurface)
				{
					pauseTextTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
					pauseTextRect = { WIDTH / 2 - 100, HEIGHT / 2 - 24, textSurface->w, textSurface->h };
					SDL_FreeSurface(textSurface);
				}
			}
			
			
			score = 0;
			highScores = {};

			pauseButton.loadTexture("assets/image/pause_button.png", renderer);
			pauseButton.setRect(WIDTH - 60, 20, 50, 50);
			resumePlayingButton.loadTexture("assets/image/resume_playing_button.png", renderer);
			resumePlayingButton.setRect(WIDTH - 60, 20, 50, 50);

			gameOverScreen = new GameOverScreen(renderer);
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

	if (GameOver)
	{
		gameOverScreen->handleEvent(event, restartRequested, exitRequested);
		if (restartRequested) {
			ResetGame();
			GameOver = false;
			Mix_ResumeMusic();
			restartRequested = false;
		}

		if (exitRequested) {
			// MENU...
			exitRequested = false;
		}
	}

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_p:
			if (!GameOver) {
				Pause = !Pause;
				if (Pause)
				{
					Mix_PauseMusic();
				}
				else
				{
					Mix_ResumeMusic();
				}
			}
		case SDLK_r:
			if (GameOver) {
				ResetGame();
				GameOver = false;
				Mix_ResumeMusic();
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		if (pauseButton.isHovering(event.button.x, event.button.y) && pauseButton.isReadyToClick())
		{
			Pause = !Pause;
			if (Pause)
			{
				Mix_PauseMusic();
			}
			else
			{
				Mix_ResumeMusic();
			}
		}
	}

	



	if (!Pause && !GameOver) {
		player.handleInput(event);
	}
}

void GameLoop::Update()
{
	if (Pause) {
		std::cout << "Game is paused" << std::endl;
		return;
	}
	if (GameOver) {
		Mix_PauseMusic();
		std::cout << "Game Over" << std::endl;

		gameOverScreen->setScore(score);
		gameOverScreen->setHighScores(highScores);
		return;
	}


	if (player.isAlive())
	{
		score++;
		//scoreNeedsUpdade = true;
	}
	else
	{
		if (waitForDeath_timer++ > 200) {
			waitForDeath_timer = 0;
			GameOver = true;
			highScores.push_back(score);
			std::sort(highScores.begin(), highScores.end());
			return;
		}
	}


// background
	int background_scrollSpeed = background.scrollSpeed;
	if (!player.isAlive()) background_scrollSpeed = 0;

	background.offSetX -= background_scrollSpeed;
	_background.offSetX -= background_scrollSpeed;
	background.BackgroundUpdate();
	_background.BackgroundUpdate();
	if (background.offSetX <= -1800)
	{
		background.offSetX = 1800;
	}
	if (_background.offSetX <= -1800)
	{
		_background.offSetX = 1800;
	}
//

// tileMap
	int scrollSpeed = curr_map.scrollSpeed;
	if (!player.isAlive()) scrollSpeed = 0;

	curr_map.offSetX -= scrollSpeed;
	next_map.offSetX -= scrollSpeed;


	CollisionManager::handleCollisions(player, curr_map);
	CollisionManager::handleCollisions(player, next_map);
	CollisionManager::handleCollisions(enemy, curr_map);
	CollisionManager::handleCollisions(enemy, next_map);
	
	if (player.isAlive()) player.setX(player.getRect().x - scrollSpeed);
	if (enemy.isAlive()) enemy.setX(enemy.getRect().x - scrollSpeed);

	if (curr_map.offSetX <= -1800) {
		curr_map = next_map;
		curr_map.offSetX = 0;

		int randomIdx = getRandomInt(0, tileMapList.size() - 1);
		next_map = tileMapList[randomIdx];
		next_map.offSetX = 1800; // mapWidth = 1800
	}
//

	if (enemyProjectile.isActive() && CollisionManager::checkCollision(player.getRect(), enemyProjectile.getRect()))
	{
		player.setHP(-1);
		enemyProjectile.setActive(false);
	}
	if (energy_attack_1.isActive() && CollisionManager::checkCollision(enemy.getRect(), energy_attack_1.getRect()))
	{
		enemy.setHP(-1);
	}
	

	player.Update();
	energy_attack_1.Update(player);
	enemyAI.Update(enemy, player, curr_map);
	enemyAI.Update(enemy, player, next_map);
	enemy.Update();
	enemyProjectile.Update(enemy);

	
	if(!enemy.isAlive() && !waitingForRevive) {
		waitingForRevive = true;
		deathTimer = 0;
	}

	if (waitingForRevive) {
		deathTimer++;
		if (deathTimer >= 300) {
			enemy.revive();
			/*enemy.setHP(1);*/
			enemy.setRect(1600, 150, 100, 100);
			enemy.setX(1600);
			enemy.setY(150);
			waitingForRevive = false;
			std::cout << "Enemy revived!" << std::endl;
		}
	}
}

void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	background.Render(renderer);
	_background.Render(renderer);
	curr_map.Render(renderer);
	next_map.Render(renderer);
		
	enemy.Render(renderer);
	player.Render(renderer);
	enemyProjectile.Render(renderer);
	energy_attack_1.Render(renderer);

	if (!Pause) pauseButton.Render(renderer);
	else resumePlayingButton.Render(renderer);

	// Score
	if (scoreFont)
	{
		SDL_DestroyTexture(scoreTextTexture);
		std::string scoreText = "Score: " + std::to_string(score);
		SDL_Color textColor = { 255, 255, 255, 255 };
		SDL_Surface* textSurface = TTF_RenderText_Solid(scoreFont, scoreText.c_str(), textColor);
		if (textSurface) {
			scoreTextTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			scoreTextRect = { 50, 40, textSurface->w, textSurface->h };
			SDL_FreeSurface(textSurface);
		}
	}
	if (scoreTextTexture) {
		SDL_RenderCopy(renderer, scoreTextTexture, NULL, &scoreTextRect);
	}


	//Paused
	if (Pause)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); // Black, 50% transparent
		SDL_Rect pauseOverlay = { 0, 0, WIDTH, HEIGHT };
		SDL_RenderFillRect(renderer, & pauseOverlay);

		if (pauseTextTexture)
		{
			SDL_RenderCopy(renderer, pauseTextTexture, NULL, &pauseTextRect);
		}
	}
	 
	// Game Over
	if (GameOver) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); // Black, 50% transparent
		SDL_Rect gameOverScreenOverlay = { 0, 0, WIDTH, HEIGHT };
		SDL_RenderFillRect(renderer, &gameOverScreenOverlay);

		gameOverScreen->Render(renderer);
	}


	SDL_RenderPresent(renderer);
}

void GameLoop::ResetGame()
{
	// Reset score
	score = 0;
	//scoreNeedsUpdate = true;

	// Reset player
	player.revive();
	player.setX(200);
	player.setY(100);
	player.setVelocityX(0);
	player.setVelocityY(0);
	player.setRect(200, 100, 100, 100);

	// Reset enemy
	enemy.revive();
	enemy.setRect(1600, 300, 100, 100);
	enemy.setVelocityX(0);
	enemy.setVelocityY(0);
	waitingForRevive = false;
	deathTimer = 0;

	// Reset map
	Tile tileMap_0;
	tileMap_0.loadTileMap("tileSet/tileSet_0.txt");  tileMap_0.setupTiles(renderer);
	curr_map = tileMap_0;
	curr_map.offSetX = 0;

	next_map = tileMapList[0]; // tileMap_1
	next_map.offSetX = 1800;


	// Reset background
	background.offSetX = 0;
	_background.offSetX = 1800;

	// Reset projectile
	energy_attack_1.setActive(false);
	enemyProjectile.setActive(false);
}

void GameLoop::Clear()
{
	
	Mix_FreeMusic(bgMusic);
	bgMusic = NULL;
	Mix_CloseAudio();

	SDL_DestroyTexture(pauseTextTexture);
	SDL_DestroyTexture(scoreTextTexture);
	TTF_CloseFont(pauseFont);
	TTF_CloseFont(scoreFont);
	TTF_Quit;
	gameOverScreen->~GameOverScreen();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}