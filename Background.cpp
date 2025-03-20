#include "Background.h"

void Background::GroundRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Background::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), NULL, NULL);
}


void Background::BackgroundUpdate()
{

	setSrc(0, 0, 1800, 1000);
	setDest(0, 0, 1800, 1000);
}