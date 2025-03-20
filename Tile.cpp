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
		}
	}
	input_file.close();
}

void Tile::setupTiles()
{
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
	return tileMap[tileMap_i][tileMap_j];
}

SDL_Rect Tile::getTileRect(int row, int col)
{
	int TILE_SIZE = 100;
	return { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };
}

void Tile::Render(SDL_Renderer* ren)
{
	tileTexture = IMG_LoadTexture(ren, "assets/image/tileset.png");

	for (int i = 0; i < MAP_LEVEL_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_LEVEL_WIDTH; j++)
		{
			int tileType = tileMap[i][j];

			SDL_Rect renderQuad = { j * 100, i * 100, 100, 100 };
			SDL_RenderCopy(ren, tileTexture, &tileClips[tileType], &renderQuad);
		}
	}
}