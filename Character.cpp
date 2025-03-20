#include "Character.h"

void Character::Render(SDL_Renderer* ren) {
	SDL_Rect* currentClip = NULL;
	SDL_Texture* currentTexture = NULL;



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
	else if (isMoving)
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



	SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	SDL_Rect renderQuad = { (int)x_pos, (int)y_pos, 100, 100 };

	SDL_RenderCopyEx(ren, currentTexture, currentClip, &renderQuad, 0, NULL, flip);
}


void Character::setSpriteSheet(SDL_Renderer* ren)
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
}


// Collisions
SDL_Rect Character::getRect()
{
	return playerRect;
}

void Character::setRect(int x, int y, int w, int h)
{
	playerRect.x = x;
	playerRect.y = y;
	playerRect.w = w;
	playerRect.h = h;
}

void Character::setY(int y_value)
{
	y_pos = y_value;
}

void Character::setX(int x_value)
{
	x_pos = x_value;
}

void Character::setVelocityY(int yVel_value)
{
	yVel = yVel_value;
}

void Character::setVelocityX(int xVel_value)
{
	xVel = xVel_value;
}



void Character::setFalling(bool T_F)
{
	isFalling = T_F;
}




void Character::handleInput(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			xVel -= speed;
			facingRight = false;
			isMoving = true;
			isAttacking = false;
			break;
		case SDLK_d:
			xVel += speed;
			facingRight = true;
			isMoving = true;
			isAttacking = false;
			break;
		case SDLK_SPACE:
			if (isOnGround && !isAttacking)
			{
				yVel = -jumpspeed;
				isOnGround = false;
				isFalling = true;
				isMoving = true;
				//isAttacking = false;
				jump_current_frame = 0;
				run_current_frame = 0;
			}
			break;
		case SDLK_j:
			if (isOnGround && !isAttacking)
			{
				isAttacking = true;
				isMoving = false;
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
		case SDLK_a:
			xVel += speed;
			isMoving = false;
			break;
		case SDLK_d:
			xVel -= speed;
			isMoving = false;
			break;
		}
	}
}

void Character::Update()
{
	if (isFalling) yVel += gravity;
	x_pos += xVel;
	y_pos += yVel;


	if (yVel > 20) yVel = 20;

	// Collision detection with the tiles
	if (!isFalling)
	{
		isOnGround = true;
		yVel = 0;
		jump_current_frame = 0;
	}


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
	else if (isMoving)
	{
		if (!isOnGround)
		{
			if (animationTimer++ >= 16)
			{
				animationTimer = 0;
				if (++jump_current_frame >= 6)
				{
					jump_current_frame = 7;
					//run_current_frame = 0;
					isFalling = true;
				}
				if (!isFalling) jump_current_frame = 0;// !
			}
		}
		else if (xVel != 0)
		{
			if (animationTimer++ >= 10)
			{
				animationTimer = 0;
				if (++run_current_frame >= 9) run_current_frame = 0;
			}
		}
		else animationTimer = 0;
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



	if (x_pos < -50) x_pos = -50;
	if (x_pos > 1750) x_pos = 1750;

	int width = 100, height = 100;

	setRect(x_pos, y_pos, width, height);
}