#include "TextureManager.h"

SDL_Texture* TextureManager::Texture(const char* fileLocation, SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(fileLocation);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return tex;
}