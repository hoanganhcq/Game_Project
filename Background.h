#pragma once
#include "Object.h"

class Background : public Object
{
private:
	int x_pos = 0;
public:
	void BackgroundUpdate();
	void Render(SDL_Renderer* ren);
	int offSetX = 0;
	int scrollSpeed = 1;
};