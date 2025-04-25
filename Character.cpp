#include "Character.h"
#include "Tile.h"
#include <iostream>

void Character::Render(SDL_Renderer* ren) {
	SDL_Rect* currentClip = NULL;
	SDL_Texture* currentTexture = NULL;

	if (!Dead)
	{
		if (isPlayer)
		{
			if (isAttacking && isOnGround)
			{
				switch (current_attack) {
				case 1:
					currentClip = &attack1_spriteClips[attack_current_frame];
					currentTexture = attack1_spritesheet;
					break;
				case 2:
					currentClip = &attack2_spriteClips[attack_current_frame];
					currentTexture = attack2_spritesheet;
					break;
				case 3:
					currentClip = &attack3_spriteClips[attack_current_frame];
					currentTexture = attack3_spritesheet;
					break;
				}
			}
			else if (isMoving || !isOnGround)
			{
				if (!isOnGround) {// jump
					currentClip = &jump_spriteClips[jump_current_frame];
					currentTexture = jump_spritesheet;
				}
				else {
					currentClip = &run_spriteClips[run_current_frame];
					currentTexture = run_spritesheet;
				}
			}
			else
			{
				currentClip = &idle_spriteClips[idle_current_frame];
				currentTexture = idle_spritesheet;
			}
		}
		else {
			if (isAttacking && isOnGround)
			{
				currentClip = &attack_monster_spriteClips[attack_monster_current_frame];
				currentTexture = attack_monster_spritesheet;
			}
			else if (isMoving || !isOnGround)
			{
				if (isOnGround) {
					currentClip = &move_monster_spriteClips[move_monster_current_frame];
					currentTexture = move_monster_spritesheet;
				}
				else // fall
				{
					currentClip = &idle_monster_spriteClips[idle_monster_current_frame];
					currentTexture = idle_monster_spritesheet;
				}
			}
			else
			{
				currentClip = &idle_monster_spriteClips[idle_monster_current_frame];
				currentTexture = idle_monster_spritesheet;
			}
		}
	}
	else {
		if (isPlayer)
		{
			//if (dead_current_frame < 10)
			//{
			//	currentClip = &dead_spriteClips[dead_current_frame];
			//	currentTexture = dead_spritesheet;
			//}// else NULL
			currentClip = &dead_spriteClips[dead_current_frame];
			currentTexture = dead_spritesheet;
		}
		else
		{
			if (dead_monster_current_frame < 6)
			{
				currentClip = &dead_monster_spriteClips[dead_monster_current_frame];
				currentTexture = dead_monster_spritesheet;
			}// else NULL
		}
	}


	SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	SDL_Rect renderQuad = { (int)x_pos, (int)y_pos, 100, 100 };
	if (isPlayer && isAttacking && isOnGround)
	{
		renderQuad = { (int)x_pos, (int)(y_pos - 18), 118, 118 };
		if (current_attack == 3) renderQuad = { (int)x_pos, (int)(y_pos - 40), 140, 140 };
	}
	SDL_RenderCopyEx(ren, currentTexture, currentClip, &renderQuad, 0, NULL, flip);
}


void Character::player_setSpriteSheet(SDL_Renderer* ren)
{
	idle_spritesheet = IMG_LoadTexture(ren, "assets/image/idle_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		idle_spriteClips[i].x = i * frameWidth;
		idle_spriteClips[i].y = 0;
		idle_spriteClips[i].w = frameWidth;
		idle_spriteClips[i].h = frameHeight;
	}

	run_spritesheet = IMG_LoadTexture(ren, "assets/image/run_spritesheet.png");
	for (int i = 0; i < 9; i++)
	{
		run_spriteClips[i].x = i * frameWidth;
		run_spriteClips[i].y = 0;
		run_spriteClips[i].w = frameWidth;
		run_spriteClips[i].h = frameHeight;
	}

	jump_spritesheet = IMG_LoadTexture(ren, "assets/image/jump_spritesheet.png");
	for (int i = 0; i < 7; i++)
	{
		jump_spriteClips[i].x = i * frameWidth;
		jump_spriteClips[i].y = 0;
		jump_spriteClips[i].w = frameWidth;
		jump_spriteClips[i].h = frameHeight;
	}

	attack1_spritesheet = IMG_LoadTexture(ren, "assets/image/attack1_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		attack1_spriteClips[i].x = i * 150;
		attack1_spriteClips[i].y = 0;
		attack1_spriteClips[i].w = 150;
		attack1_spriteClips[i].h = 100;
	}
	attack2_spritesheet = IMG_LoadTexture(ren, "assets/image/attack2_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		attack2_spriteClips[i].x = i * 150;
		attack2_spriteClips[i].y = 0;
		attack2_spriteClips[i].w = 150;
		attack2_spriteClips[i].h = 100;
	}
	attack3_spritesheet = IMG_LoadTexture(ren, "assets/image/attack3_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		attack3_spriteClips[i].x = i * 150;
		attack3_spriteClips[i].y = 0;
		attack3_spriteClips[i].w = 150;
		attack3_spriteClips[i].h = 100;
	}
	dead_spritesheet = IMG_LoadTexture(ren, "assets/image/dead_spritesheet.png");
	for (int i = 0; i < 10; i++) {
		dead_spriteClips[i].x = i * 200;
		dead_spriteClips[i].y = 0;
		dead_spriteClips[i].w = 200;
		dead_spriteClips[i].h = 150;
	}
}

void Character::player_setAudio()
{
	runSound = Mix_LoadWAV("assets/audio/footStep.wav");
	attackSound = Mix_LoadWAV("assets/audio/player_attack.wav");
	Mix_VolumeChunk(attackSound, 32);
	jumpSound = Mix_LoadWAV("assets/audio/jump.wav");

	playerDiedSound = Mix_LoadWAV("assets/audio/playerDied.wav");
	Mix_VolumeChunk(playerDiedSound, 16);
}

void Character::enemy_setSpriteSheet(SDL_Renderer* ren) {
	
	idle_monster_spritesheet = IMG_LoadTexture(ren, "assets/image/idle_monster.png");
	for (int i = 0; i < 9; i++)
	{
		idle_monster_spriteClips[i].x = i * frameWidth;
		idle_monster_spriteClips[i].y = 0;
		idle_monster_spriteClips[i].w = frameWidth;
		idle_monster_spriteClips[i].h = frameHeight;
	}

	move_monster_spritesheet = IMG_LoadTexture(ren, "assets/image/move_monster.png");
	for (int i = 0; i < 10; i++)
	{
		move_monster_spriteClips[i].x = i * frameWidth;
		move_monster_spriteClips[i].y = 0;
		move_monster_spriteClips[i].w = frameWidth;
		move_monster_spriteClips[i].h = frameHeight;
	}

	dead_monster_spritesheet = IMG_LoadTexture(ren, "assets/image/dead_monster.png");
	for (int i = 0; i < 6; i++)
	{
		dead_monster_spriteClips[i].x = i * frameWidth;
		dead_monster_spriteClips[i].y = 0;
		dead_monster_spriteClips[i].w = frameWidth;
		dead_monster_spriteClips[i].h = frameHeight;
	}

	attack_monster_spritesheet = IMG_LoadTexture(ren, "assets/image/attack_monster.png");
	for (int i = 0; i < 4; i++)
	{
		attack_monster_spriteClips[i].x = i * frameWidth;
		attack_monster_spriteClips[i].y = 0;
		attack_monster_spriteClips[i].w = frameWidth;
		attack_monster_spriteClips[i].h = frameHeight;
	}
}

// Collisions
SDL_Rect Character::getRect()
{
	return characterRect;
}

void Character::setRect(float x, float y, int w, int h)
{
	characterRect.x = x;
	characterRect.y = y;
	characterRect.w = w;
	characterRect.h = h;
}

void Character::setY(float y_value)
{
	y_pos = y_value;
}

void Character::setX(float x_value)
{
	x_pos = x_value;
}


void Character::setVelocityY(float yVel_value)
{
	yVel = yVel_value;
}

void Character::setVelocityX(float xVel_value)
{
	xVel = xVel_value;
}

float Character::getVelocityY()
{
	return yVel;
}

float Character::getVelocityX()
{
	return xVel;
}


void Character::setFalling(bool T_F)
{
	isFalling = T_F;
}

bool Character::getJumpState()
{
	return isFalling;
}


bool Character::getDirection()
{
	return facingRight;
}

void Character::setDirection(bool facing_right)
{
	facingRight = facing_right;
}

bool Character::getAttackState()
{
	return isAttacking;
}

void Character::setHP(int amountOfChange) {
	healthPoints += amountOfChange;
}

void Character::revive() {
	Dead = false;
	dead_current_frame = 0;
	dead_monster_current_frame = 0;
	setHP(1);

	isOnGround = false;
	isMoving = false;
	facingRight = true;
	isAttacking = false;
}


void Character::handleInput(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_a: {
				xVel = -0.75f * speed;
				facingRight = false;
				isMoving = true;
				isAttacking = false;
			
				if (isOnGround && isMoving && !Mix_Playing(runChannel)) {
					runChannel = Mix_PlayChannel(-1, runSound, -1); // -1 : loop
				}
				break;
			}
			case SDLK_d: {
				xVel = 1.50f * speed;
				facingRight = true;
				isMoving = true;
				isAttacking = false;

				if (isOnGround && isMoving && !Mix_Playing(runChannel)) {
					runChannel = Mix_PlayChannel(-1, runSound, -1); // -1 : loop
				}
				break;
			}
			case SDLK_SPACE: {
				if (isOnGround && !isAttacking)
				{
					Mix_PlayChannel(-1, jumpSound, 0);
					yVel = -jumpspeed;
					isOnGround = false;
					isFalling = true;
					isMoving = true;
					//isAttacking = false;
					jump_current_frame = 0;
					run_current_frame = 0;
				}
				if (runChannel != -1) {
					Mix_HaltChannel(runChannel);
					runChannel = -1;
				}
				break;
			}
			case SDLK_j: {
				if (isOnGround && !isAttacking)
				{
					Mix_PlayChannel(-1, attackSound, 0);
					isAttacking = true;
					xVel = 0;
					isMoving = false;
					current_attack = (current_attack % 3) + 1;
					attack_current_frame = 0;
				}
				if (runChannel != -1) {
					Mix_HaltChannel(runChannel);
					runChannel = -1;
				}
				break;
			}
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_a: {
				if (xVel < 0) xVel = 0;
				isMoving = false;
				if (runChannel != -1) {
					Mix_HaltChannel(runChannel);
					runChannel = -1;
				}
				break;
			}
			case SDLK_d: {
				if (xVel > 0) xVel = 0;
				isMoving = false;
				if (runChannel != -1) {
					Mix_HaltChannel(runChannel);
					runChannel = -1;
				}
				break;
			}
		}
	}
}


void Character::Update()
{
	if (!Dead)
	{
		if (isFalling) {
			yVel += gravity;
		}
		else yVel = 0;
		x_pos += xVel;
		y_pos += yVel;


		if (yVel > 20) yVel = 20;

		if (isPlayer)
		{
			// Collision detection with the tiles
			if (!isFalling)
			{
				isOnGround = true;
				jump_current_frame = 0;
			}
			else isOnGround = false;


			if (isAttacking)
			{
				if (animationTimer++ >= 8)
				{
					animationTimer = 0;
					if (++attack_current_frame >= 6)
					{
						attack_current_frame = 0;
						isAttacking = false;
					}
				}
			}
			else if (isMoving || !isOnGround)
			{
				if (!isOnGround)
				{
					if (animationTimer++ >= 16)
					{
						animationTimer = 0;
						if (++jump_current_frame >= 6)
						{
							jump_current_frame = 6;
						}
					}
				}
				else if (xVel != 0)
				{
					if (animationTimer++ >= 8)
					{
						animationTimer = 0;
						if (++run_current_frame >= 9) run_current_frame = 0;
					}
				}
				else {
					animationTimer = 0;
					isMoving = false;
				}
			}
			else
			{
				if (animationTimer++ >= 16)
				{
					animationTimer = 0;
					if (++idle_current_frame >= 6)
					{
						idle_current_frame = 0;
					}
				}
			}
		}
		else {
			if (!isFalling)
			{
				isOnGround = true;

				jump_current_frame = 0;
			}
			else isOnGround = false;


			if (isAttacking)
			{
				if (animationTimer++ >= 15)
				{
					animationTimer = 0;
					if (++attack_monster_current_frame >= 4)
					{
						attack_monster_current_frame = 0;
						isAttacking = false;
					}
				}
			}
			else if (isMoving && isOnGround)
			{
				if (xVel != 0)
				{
					if (animationTimer++ >= 8)
					{
						animationTimer = 0;
						if (++move_monster_current_frame >= 9) move_monster_current_frame = 0;
					}
				}
				else {
					animationTimer = 0;
					isMoving = false;
				}
			}
			else
			{
				if (animationTimer++ >= 16)
				{
					animationTimer = 0;
					if (++idle_monster_current_frame >= 9)
					{
						idle_monster_current_frame = 0;
					}
				}
			}
		}


		if (x_pos < -80) Dead = true;
		if (isPlayer && x_pos > 1750) x_pos = 1750;
		if (y_pos > 1200) Dead = true;

		setRect(x_pos, y_pos, 100, 100);
	}
	else  // dead
	{
		if (isFalling) yVel += gravity;
		y_pos += yVel;

		if (isPlayer)
		{
			if (animationTimer++ >= 18)
			{
				animationTimer = 0;
				if (dead_current_frame++ >= 9)
				{
					dead_current_frame = 9;
				}
			}
		}
		else
		{
			if (animationTimer++ >= 15)
			{
				animationTimer = 0;
				if (dead_monster_current_frame++ >= 6)
				{
					dead_monster_current_frame = 6;//...
				}
			}
		}
	}

	if (healthPoints <= 0)
	{
		Dead = true;
		healthPoints = 0;
	}


	if (isPlayer && Dead) Mix_PlayChannel(-1, playerDiedSound, 0);
}