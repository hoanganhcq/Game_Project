#pragma once
#include <SDL.h>
#include "Object.h"

class Character : public Object
{
private:
	float x_pos = 1200, y_pos = 400;
	float xVel = 0, yVel = 0;

	float speed = 4;
	float jumpspeed = 10;
	float gravity = 0.2;

	bool isPlayer = false;
	bool Dead = false;
	int healthPoints = 3;

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



	SDL_Texture* idle_monster_spritesheet = NULL;
	SDL_Rect idle_monster_spriteClips[9];
	int idle_monster_current_frame = 0;

	SDL_Texture* move_monster_spritesheet = NULL;
	SDL_Rect move_monster_spriteClips[10];
	int move_monster_current_frame = 0;

	SDL_Texture* dead_monster_spritesheet = NULL;
	SDL_Rect dead_monster_spriteClips[6];
	int dead_monster_current_frame = 0;

	SDL_Texture* attack_monster_spritesheet = NULL;
	SDL_Rect attack_monster_spriteClips[4];
	int attack_monster_current_frame = 0;


	SDL_Rect characterRect;

	int animationTimer = 0;
public:
	void setPlayer() { isPlayer = true; }

	SDL_Rect getRect();
	void setRect(float x, float y, int w, int h);
	void setY(float y_value);
	void setX(float x_value);
	void setVelocityY(float yVel_value);
	void setVelocityX(float xVel_value);
	float getVelocityY();
	float getVelocityX();
	void setFalling(bool T_F);
	bool getJumpState();

	//
	bool getDirection();
	void setDirection(bool facing_right);
	bool getAttackState();
	void setAttackState(bool attacking) { isAttacking = attacking; }

	bool isAlive() const { return !Dead; }
	int getHP() const { return healthPoints; }
	void setHP(int amountOfChange);
	void revive() { Dead = false; }


	void Render(SDL_Renderer* ren);
	void handleInput(SDL_Event& event);
	void player_setSpriteSheet(SDL_Renderer* ren);
	void Update();

	void enemy_setSpriteSheet(SDL_Renderer* ren);
};