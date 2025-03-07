#include "Character.h"

void Character::Render(SDL_Renderer* ren)
{
	animationTimer++;
	SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), NULL, NULL, SDL_FLIP_NONE);

}

void Character::Movement(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				x_pos -= speed;
				break;
			case SDLK_RIGHT:
				x_pos += speed;
				break;
			case SDLK_UP:
				y_pos -= speed;
				break;
			case SDLK_DOWN:
				y_pos += speed;
				break;
		}
	}
}

void Character::PositionUpdate()
{
	setSrc(0, 0, 50, 50);
	setDest(x_pos, y_pos, 50, 50);
}