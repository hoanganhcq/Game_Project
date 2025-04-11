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
	enemy.setRect(1600, 200, 100, 100);
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
		cout << "Created Window" << endl;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			GameState = true;
			background.CreateTexture("assets/image/game_background.png", renderer);
			_background.CreateTexture("assets/image/game_background.png", renderer); _background.offSetX = 1800;
			player.player_setSpriteSheet(renderer);
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
// background
	background.offSetX -= background.scrollSpeed;
	_background.offSetX -= _background.scrollSpeed;
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
	curr_map.offSetX -= scrollSpeed;
	next_map.offSetX -= scrollSpeed;


	CollisionManager::handleCollisions(player, curr_map);
	CollisionManager::handleCollisions(player, next_map);
	CollisionManager::handleCollisions(enemy, curr_map);
	CollisionManager::handleCollisions(enemy, next_map);
	
	player.setX(player.getRect().x - scrollSpeed);
	enemy.setX(enemy.getRect().x - scrollSpeed);

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
		/*energy_attack_1.setActive(false);*/
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
			enemy.setHP(1);
			enemy.setRect(1600, 50, 100, 100);
			enemy.setX(1600);
			enemy.setY(50);
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

	SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}