#include "Menu.h"

Menu::Menu(SDL_Renderer* ren)
{
	TTF_Init();
	font = TTF_OpenFont("assets/truetype_font/Poppins-Bold.ttf", 64);
	backgroundTexture = IMG_LoadTexture(ren, "assets/image/menuBackground.png");
	playButton.loadTexture("assets/image/playButton.png", ren);
	playButton.setRect(800, 550, 260, 100);
	quitButton.loadTexture("assets/image/quitButton.png", ren);
	quitButton.setRect(800, 700, 260, 100);
}

void Menu::renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, bool centered) {
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect dst = { x, y, surface->w, surface->h };
	if (centered) {
		dst.x -= surface->w / 2;
	}

	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Menu::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);

	SDL_Color yellow = { 255, 215, 0 };
	renderText(ren, "Twilight Run", 920, 300, yellow, true);

	playButton.Render(ren);
	quitButton.Render(ren);
}

void Menu::handleEvent(SDL_Event& event, bool& playRequested, bool& quitRequested)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		int mx = event.button.x;
		int my = event.button.y;

		if (playButton.isHovering(mx, my)) {
			playRequested = true;
		}

		if (quitButton.isHovering(mx, my)) {
			quitRequested = true;
		}
	}
}