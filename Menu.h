#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Button.h"

class Menu
{
private:
	TTF_Font* font;
	std::string title = "Twilight Run";
	SDL_Texture* backgroundTexture;

	Button playButton;
	Button quitButton;

	void renderText(SDL_Renderer* ren, const std::string& text, int x, int y, SDL_Color color, bool center = true);
public:
	Menu(SDL_Renderer* renderer);
	void Render(SDL_Renderer* ren);
	void handleEvent(SDL_Event& event, bool& playRequested, bool& quitRequested);
};