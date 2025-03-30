#pragma once
#include "CollisionManager.h"
#include <iostream>

bool CollisionManager::checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y);
}

void CollisionManager::handleCollisions(Character& player, Tile& tile) {
    SDL_Rect playerRect = player.getRect();
    float velocityX = player.getVelocityX();
    float velocityY = player.getVelocityY();

    int x1, x2, y1, y2, t_x1, t_x2;

    // Horizontal collision
    int min_height = (playerRect.h < TILE_SIZE) ? playerRect.h : TILE_SIZE;
    x1 = (playerRect.x + velocityX) / TILE_SIZE;
    x2 = (playerRect.x + velocityX + playerRect.w - 1) / TILE_SIZE;
    y1 = playerRect.y / TILE_SIZE;
    y2 = (playerRect.y + min_height - 1) / TILE_SIZE;

    t_x1 = (playerRect.x + velocityX - tile.offSetX) / TILE_SIZE;
    t_x2 = (playerRect.x + velocityX + playerRect.w - 1 - tile.offSetX) / TILE_SIZE;

    if (t_x1 >= 0 && t_x2 < MAP_LEVEL_WIDTH && y1 >= 0 && y2 < MAP_LEVEL_HEIGHT) {
        if (velocityX > 0) {
            if (tile.getTileType(y1, t_x2) != 0 || (tile.getTileType(y2, t_x2) != 0 && velocityY == 0)) {
                player.setX(t_x2 * TILE_SIZE + tile.offSetX - playerRect.w);
                player.setVelocityX(0);
            }
        }
        else if (velocityX < 0) {
            if (tile.getTileType(y1, t_x1) != 0 || (tile.getTileType(y2, t_x1) != 0 && velocityY == 0)) {
                player.setX((t_x1 + 1) * TILE_SIZE + tile.offSetX);
                player.setVelocityX(0);
            }
        }
    }

    // Vertical collision
    int min_width = (playerRect.w < TILE_SIZE) ? playerRect.w : TILE_SIZE;
    x1 = playerRect.x / TILE_SIZE;
    x2 = (playerRect.x + min_width - 1) / TILE_SIZE;
    y1 = (playerRect.y + velocityY) / TILE_SIZE;
    y2 = (playerRect.y + velocityY + playerRect.h - 1) / TILE_SIZE;

    t_x1 = (playerRect.x - tile.offSetX) / TILE_SIZE;
    t_x2 = (playerRect.x + min_width - 1 - tile.offSetX) / TILE_SIZE;

    bool wasFalling = player.getJumpState();

    if (t_x1 >= 0 && t_x2 < MAP_LEVEL_WIDTH && y1 >= 0 && y2 < MAP_LEVEL_HEIGHT) {
        if (velocityY > 0) {
            if (tile.getTileType(y2, t_x1) != 0 || tile.getTileType(y2, t_x2) != 0) {
                player.setY(y2 * TILE_SIZE - playerRect.h);
                player.setVelocityY(0);
                player.setFalling(false);
            }
            else if (wasFalling) {
                player.setFalling(true);
            }
        }
        else if (velocityY < 0) {
            if (tile.getTileType(y1, t_x1) != 0 || tile.getTileType(y1, t_x2) != 0) {
                player.setY((y1 + 1) * TILE_SIZE);
                player.setVelocityY(0);
            }
        }
    }

    int bottom_y = (playerRect.y + playerRect.h) / TILE_SIZE;
    int bottom_x1 = (playerRect.x - tile.offSetX) / TILE_SIZE;
    int bottom_x2 = (playerRect.x + min_width - 1 - tile.offSetX) / TILE_SIZE;

    if (bottom_x1 >= 0 && bottom_x2 < MAP_LEVEL_WIDTH && bottom_y < MAP_LEVEL_HEIGHT) {
        if (tile.getTileType(bottom_y, bottom_x1) == 0 && tile.getTileType(bottom_y, bottom_x2) == 0) {
            player.setFalling(true);
        }
    }
}