#pragma once
#include <SDL_image.h>

#define MAP_LEVEL_WIDTH 18
#define MAP_LEVEL_HEIGHT 10

class Tile
{
private:
	int tileMap[MAP_LEVEL_HEIGHT][MAP_LEVEL_WIDTH];
	SDL_Texture* tileTexture = NULL;
	SDL_Rect tileClips[3];  // for 3 types of tile
public:
	void loadTileMap(const char* path);
	void setupTiles();
	int getTileType(int tileMap_i, int tileMap_j);
	SDL_Rect getTileRect(int row, int col);
	void Render(SDL_Renderer* ren);
};