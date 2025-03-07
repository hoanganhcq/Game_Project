#pragma once
#include <SDL.h>
#include "Object.h"

class Character : public Object
{
private:
	int x_pos = 200, y_pos = 200;
	int speed = 20;

	SDL_Texture* Tex = NULL;
	int animationTimer = 0;
public:
	

	void Render(SDL_Renderer* ren);
	void Movement(SDL_Event& event);
	void PositionUpdate();
};