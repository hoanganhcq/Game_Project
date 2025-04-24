#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Button.h"

class PauseContainer
{
private:
	SDL_Texture* containerTexture = NULL;
	SDL_Rect containerRect;

	SDL_Texture* resumeTextTex = NULL;
	SDL_Texture* exitTextTex = NULL;
	SDL_Rect resumeTextRect;
	SDL_Rect exitTextRect;
	Mix_Chunk* pressed_sound = NULL;
public:
	PauseContainer();
	Button resumeButton;
	Button exitButton;

	void setRect(int x, int y, int w, int h);
	void loadTexture(SDL_Renderer* ren);
	void loadButtons(SDL_Renderer* ren);
	void loadTexts(SDL_Renderer* ren, TTF_Font* font);
	void handleEvent(SDL_Event& event, bool& resumeRequested, bool& exitRequested);
	void Render(SDL_Renderer* ren);
};