#pragma once
#include "CollisionManager.h"

bool CollisionManager::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

void CollisionManager::handleCollisions(Character& player, Tile& tile) {
    bool falling = true;

    for (int i = 0; i < MAP_LEVEL_HEIGHT; i++) {
        for (int j = 0; j < MAP_LEVEL_WIDTH; j++) {
            if (tile.getTileType(i, j) != 0) { // is Solid
                SDL_Rect tileRect = tile.getTileRect(i, j);
                SDL_Rect playerRect = player.getRect();

                if (checkCollision(playerRect, tileRect)) {
                    int playerBottom = playerRect.y + playerRect.h;
                    int playerTop = playerRect.y;
                    int playerLeft = playerRect.x;
                    int playerRight = playerRect.x + playerRect.w;

                    int tileBottom = tileRect.y + tileRect.h;
                    int tileTop = tileRect.y;
                    int tileLeft = tileRect.x;
                    int tileRight = tileRect.x + tileRect.w;

                    // fall to Tile
                    if (playerBottom > tileTop && playerRect.y < tileTop) {
                        if (i == 0 || tile.getTileType(i - 1, j) == 0) 
                        { // Ensure no tile directly above
                            player.setY(tileTop - playerRect.h);
                            player.setVelocityY(0);
                            falling = false;
                        }
                        /*player.setY(tileTop - playerRect.h);
                        player.setVelocityY(0);
                        falling = false;*/
                    }
                    // up to Tile
                    else if (playerTop < tileBottom && playerBottom > tileBottom) {
                        /*if (i < MAP_LEVEL_HEIGHT - 1 && tile.getTileType(i + 1, j) == 0)
                        {
                            player.setY(tileBottom);
                            player.setVelocityY(0);
                        }*/
                        player.setY(tileBottom);
                        player.setVelocityY(0);

                    }
                         // left to Tile
                    else if (playerRight > tileLeft && playerLeft < tileLeft) {
                        player.setX(tileLeft - playerRect.w);
                        
                    }
                         // right to Tile
                    else if (playerLeft < tileRight && playerRight > tileRight) {
                        player.setX(tileRight);
                        
                    }
                }
            }
        }
    }
    player.setFalling(falling);
}