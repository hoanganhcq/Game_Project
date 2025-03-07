#pragma once
#include "Object.h"

class Background : public Object
{
private:
	int x_pos = 0;
public:
	void BackgroundUpdate();
	void GroundRender(SDL_Renderer* ren);
	void Render(SDL_Renderer* ren);
};