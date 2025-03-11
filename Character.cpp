#include "Character.h"

void Character::Render(SDL_Renderer* ren) {
	SDL_Rect* currentClip = NULL;
	SDL_Texture* currentTexture = NULL;



	if (isAttacking == true && inJump == false)
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
	else if (isMoving)
	{
		if (inJump) {
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

	
	SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	SDL_Rect renderQuad = { (int)x_pos, (int)y_pos, 180, 180 };
	if (isAttacking == true && inJump == false && current_attack == 3)
	{
		if (flip == SDL_FLIP_HORIZONTAL)
		{
			renderQuad = { (int)x_pos, (int)y_pos, 200, 200 };
		}else renderQuad = { (int)x_pos, (int)y_pos, 280, 200 };
	}
	SDL_RenderCopyEx(ren, currentTexture, currentClip, &renderQuad, 0, NULL, flip);
}


void Character::setSpriteSheet(SDL_Renderer* ren)
{
	idle_spritesheet = IMG_LoadTexture(ren, "assets/image/idle_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		idle_spriteClips[i].x = i * idle_frameWidth;
		idle_spriteClips[i].y = 0;
		idle_spriteClips[i].w = idle_frameWidth;
		idle_spriteClips[i].h = idle_frameHeight;
	}

	run_spritesheet = IMG_LoadTexture(ren, "assets/image/run_spritesheet.png");
	for (int i = 0; i < 9; i++)
	{
		run_spriteClips[i].x = i * run_frameWidth;
		run_spriteClips[i].y = 0; 
		run_spriteClips[i].w = run_frameWidth;
		run_spriteClips[i].h = run_frameHeight;
	}

	jump_spritesheet = IMG_LoadTexture(ren, "assets/image/jump_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		jump_spriteClips[i].x = i * jump_frameWidth;
		jump_spriteClips[i].y = 0;
		jump_spriteClips[i].w = jump_frameWidth;
		jump_spriteClips[i].h = jump_frameHeight;
	}

	attack1_spritesheet = IMG_LoadTexture(ren, "assets/image/attack1_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		attack1_spriteClips[i].x = i * 220;
		attack1_spriteClips[i].y = 0;
		attack1_spriteClips[i].w = 220;
		attack1_spriteClips[i].h = 160;
	}
	attack2_spritesheet = IMG_LoadTexture(ren, "assets/image/attack2_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		attack2_spriteClips[i].x = i * 220;
		attack2_spriteClips[i].y = 0;
		attack2_spriteClips[i].w = 220;
		attack2_spriteClips[i].h = 160;
	}
	attack3_spritesheet = IMG_LoadTexture(ren, "assets/image/attack3_spritesheet.png");
	for (int i = 0; i < 6; i++)
	{
		attack3_spriteClips[i].x = i * 250;
		attack3_spriteClips[i].y = 0;
		attack3_spriteClips[i].w = 250;
		attack3_spriteClips[i].h = 200;
	}
}

bool Character::isOnGround()
{
	return y_pos >= 800; // groundLevel = 800
}

void Character::handleInput(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				xVel -= speed;
				facingRight = false;
				isMoving = true;
				isAttacking = false;
				break;
			case SDLK_RIGHT:
				xVel += speed;
				facingRight = true;
				isMoving = true;
				isAttacking = false;
				break;
			case SDLK_SPACE:
				if (isOnGround() && inJump == false) 
				{
					yVel = -jumpspeed;
					inJump = true;
					isMoving = true;
					isAttacking = false;
					jump_current_frame = 0;
					run_current_frame = 0;
				}
				break;
			case SDLK_j:
				if (isOnGround() == true && inJump == false && isAttacking == false)
				{
					isAttacking = true;
					/*isMoving = false;*/
					current_attack = (current_attack % 3) + 1;
					
					attack_current_frame = 0;
				}
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				xVel += speed;
				isMoving = false;
				break;
			case SDLK_RIGHT:
				xVel -= speed;
				isMoving = false;
				break;
		}
	}
}

void Character::Update()
{
	yVel += gravity;
	// update position
	x_pos += xVel;
	y_pos += yVel;


	// Collision detection with the ground
	if (y_pos > 800)
	{
		y_pos = 800;
		yVel = 0;
		inJump = false;
		jump_current_frame = 0;
	}


	if (isAttacking == true && inJump == false)
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
	else if (isMoving)
	{
		if (inJump)
		{

			if (animationTimer++ >= 16)
			{
				animationTimer = 0;
				if (++jump_current_frame >= 6)
				{
					run_current_frame = 0;
					inJump = false;
				}
			}
		}
		else if (xVel != 0)
		{
			if (animationTimer++ >= 12)
			{
				animationTimer = 0;
				if (++run_current_frame >= 9) run_current_frame = 0;
			}
		}
		else animationTimer = 0;
	}
	else
	{
		if (animationTimer++ >= 15)
		{
			animationTimer = 0;
			if (++idle_current_frame >= 6)
			{
				idle_current_frame = 0;
			}
		}
	}
}