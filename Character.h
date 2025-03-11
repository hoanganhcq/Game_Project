#pragma once
#include <SDL.h>
#include "Object.h"

class Character : public Object
{
private:
	float x_pos = 200, y_pos = 200;
	float xVel = 0, yVel = 0;

	float speed = 5;
	float jumpspeed = 8;
	float gravity = 0.2;

	bool isDead = false;
	bool inJump = false;
	bool isMoving = false;
	bool facingRight = true;
	bool isAttacking = false;

	SDL_Texture* Tex = NULL;

	//spritesheet
	SDL_Texture* idle_spritesheet = NULL;
	const int idle_frameWidth = 160, idle_frameHeight = 160;
	SDL_Rect idle_spriteClips[6];
	int idle_current_frame = 0;

	SDL_Texture* run_spritesheet = NULL;
	const int run_frameWidth = 160, run_frameHeight = 160;
	SDL_Rect run_spriteClips[9];
	int run_current_frame = 0;

	SDL_Texture* jump_spritesheet = NULL;
	const int jump_frameWidth = 130, jump_frameHeight = 140;
	SDL_Rect jump_spriteClips[6];
	int jump_current_frame = 0;


	SDL_Texture* attack1_spritesheet = NULL;
	SDL_Rect attack1_spriteClips[6];
	SDL_Texture* attack2_spritesheet = NULL;
	SDL_Rect attack2_spriteClips[6];
	SDL_Texture* attack3_spritesheet = NULL;
	SDL_Rect attack3_spriteClips[6];
	int attack_current_frame = 0;
	int current_attack = 0;

	int animationTimer = 0;
public:
	
	bool isOnGround();
	void Render(SDL_Renderer* ren);
	void handleInput(SDL_Event& event);
	void setSpriteSheet(SDL_Renderer* ren);
	void Update();
};