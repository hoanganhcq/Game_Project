#pragma once
#include <SDL_image.h>


#define MAP_LEVEL_WIDTH 18
#define MAP_LEVEL_HEIGHT 10
#define TILE_SIZE 100

class Tile
{
private:
	int tileMap[MAP_LEVEL_HEIGHT][MAP_LEVEL_WIDTH];
	SDL_Rect tilesRect[MAP_LEVEL_HEIGHT][MAP_LEVEL_WIDTH];
	SDL_Texture* tileTexture = NULL;
	SDL_Rect tileRect;
	SDL_Rect tileClips[3];  // 3 types of tile

public:
	void loadTileMap(const char* path);
	void setupTiles(SDL_Renderer* ren);
	int getTileType(int tileMap_i, int tileMap_j);
	SDL_Rect getTileRect(int row, int col);
	void Render(SDL_Renderer* ren);

	void updateScroll() { offSetX -= scrollSpeed; }

	int offSetX = 0, scrollSpeed = 2;
};