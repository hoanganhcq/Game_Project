#pragma once
#include <SDL.h>
#include "TextureManager.h"

class Button
{
private:
	SDL_Rect buttonRect;
	SDL_Rect originalRect;
	SDL_Texture* buttonTexture = NULL;
	SDL_Texture* pressedTexure = NULL;
	SDL_Texture* hoverTexture = NULL;

	bool isPressed = false;
	bool hovering = false;

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
	void loadHoverTexure(const char* fileLocation, SDL_Renderer* ren);
	void setPressedTexture(const char* fileLocation, SDL_Renderer* ren);

	void setPressed(bool pressed);
	bool getPressed() const;
	void setHover(bool T_F) { hovering = T_F; }
	bool isReadyToClick();
};
