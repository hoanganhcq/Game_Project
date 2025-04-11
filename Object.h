#pragma once
#include "TextureManager.h"

class Object
{
private:
	SDL_Rect src = { 0, 0, 0, 0 };
	SDL_Rect dest = { 0, 0, 0, 0 };
	SDL_Texture* Tex = NULL;
public:
	SDL_Texture* getTexture();
	SDL_Rect& getSrc();
	SDL_Rect& getDest();
	void setSrc(int x, int y, int w, int h);
	void setDest(int x, int y, int w, int h);

	void CreateTexture(const char* address, SDL_Renderer* ren);
	void virtual Render(SDL_Renderer* ren) = 0;
};