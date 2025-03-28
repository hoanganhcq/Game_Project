#pragma once
#include <SDL.h>
#include "Object.h"

class Character : public Object
{
private:
	float x_pos = 200, y_pos = 400;
	float xVel = 0, yVel = 0;

	float speed = 5;
	float jumpspeed = 10;
	float gravity = 0.2;

	bool isDead = false;
	//bool inJump = false;
	bool isOnGround = false;
	bool isFalling = true;
	bool isMoving = false;
	bool facingRight = true;
	bool isAttacking = false;

	SDL_Texture* Tex = NULL;

	const int frameWidth = 100;
	const int frameHeight = 100;

	//spritesheet
	SDL_Texture* idle_spritesheet = NULL;
	SDL_Rect idle_spriteClips[6];
	int idle_current_frame = 0;

	SDL_Texture* run_spritesheet = NULL;
	SDL_Rect run_spriteClips[9];
	int run_current_frame = 0;

	SDL_Texture* jump_spritesheet = NULL;
	SDL_Rect jump_spriteClips[7];
	int jump_current_frame = 0;


	SDL_Texture* attack1_spritesheet = NULL;
	SDL_Rect attack1_spriteClips[6];
	SDL_Texture* attack2_spritesheet = NULL;
	SDL_Rect attack2_spriteClips[6];
	SDL_Texture* attack3_spritesheet = NULL;
	SDL_Rect attack3_spriteClips[6];
	int attack_current_frame = 0;
	int current_attack = 0;

	SDL_Rect playerRect;
	SDL_Rect prevRect;
	int animationTimer = 0;
public:

	// Collision with Tiles
	SDL_Rect getRect();
	void setRect(int x, int y, int w, int h);
	void setY(int y_value);
	void setX(int x_value);
	void setVelocityY(int yVel_value);
	void setVelocityX(int xVel_value);
	float getVelocityY();
	float getVelocityX();
	void setFalling(bool T_F);
	bool getJumpState();


	void Render(SDL_Renderer* ren);
	void handleInput(SDL_Event& event);
	void setSpriteSheet(SDL_Renderer* ren);
	void Update();
};