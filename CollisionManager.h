#pragma once
#include "Tile.h"
#include "Character.h"

class CollisionManager
{
public:
	static bool checkCollision(SDL_Rect a, SDL_Rect b);
	static void handleCollisions(Character& player, Tile& tile_map);
};