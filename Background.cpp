#include "Background.h"

void Background::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}


void Background::BackgroundUpdate()
{
	setSrc(0, 0, 1800, 1000);
	setDest(offSetX, 0, 1800, 1000);
}