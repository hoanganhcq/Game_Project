#pragma once
#include <SDL.h>
#include "TextureManager.h"

class Button
{
private:
	SDL_Rect buttonRect;
	SDL_Texture* buttonTexture = NULL;

	Uint32 lastClickTime = 0;
	const Uint32 clickDelay = 300;  // ms
public:
	Button();
	Button(int x, int y, int w, int h, SDL_Texture* texture);
	void Render(SDL_Renderer* ren);
	bool isHovering(int mouseX, int mouseY) const;

	void setRect(int x, int y, int w, int h);
	SDL_Rect getRect();
	void loadTexture(const char* fileLocation, SDL_Renderer* ren);

	
	bool isReadyToClick();
};