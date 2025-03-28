#include "Tile.h"
#include <iostream>
#include <fstream>


void Tile::loadTileMap(const char* path)
{
	std::ifstream input_file(path);
	if (!input_file.is_open())
	{
		std::cout << "Can't open TileMap file" << std::endl;
		return;
	}

	for (int i = 0; i < MAP_LEVEL_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_LEVEL_WIDTH; j++)
		{
			input_file >> tileMap[i][j];
			if (input_file.peek() == ',') input_file.ignore();

			tilesRect[i][j].x = j * TILE_SIZE;
			tilesRect[i][j].y = i * TILE_SIZE;
			tilesRect[i][j].h = TILE_SIZE;
			tilesRect[i][j].w = TILE_SIZE;
		}
	}
	input_file.close();
}

void Tile::setupTiles(SDL_Renderer* ren)
{
	tileTexture = IMG_LoadTexture(ren, "assets/image/tileset.png");
	if (!tileTexture) {
		std::cout << "Failed to load tileset: " << IMG_GetError() << std::endl;
	}

	for (int i = 0; i < 3; i++)
	{
		tileClips[i].x = i * 100;
		tileClips[i].y = 0;
		tileClips[i].w = 100;
		tileClips[i].h = 100;
	}
}

int Tile::getTileType(int tileMap_i, int tileMap_j)
{
	if (tileMap_i < 0 || tileMap_i >= MAP_LEVEL_HEIGHT || tileMap_j < 0 || tileMap_j >= MAP_LEVEL_WIDTH) return 0;
	return tileMap[tileMap_i][tileMap_j];
}

SDL_Rect Tile::getTileRect(int row, int col)
{
	return tilesRect[row][col];
}

void Tile::Render(SDL_Renderer* ren)
{
	for (int i = 0; i < MAP_LEVEL_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_LEVEL_WIDTH; j++)
		{
			int tileType = tileMap[i][j];
			SDL_Rect renderQuad = { tilesRect[i][j].x + offSetX, tilesRect[i][j].y, TILE_SIZE, TILE_SIZE};
			SDL_RenderCopy(ren, tileTexture, &tileClips[tileType], &renderQuad);
		}
	}
}