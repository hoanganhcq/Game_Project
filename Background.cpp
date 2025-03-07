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

	setSrc(0, 0, 1050, 1050);
	setDest(0, 0, 1080, 1080);
}