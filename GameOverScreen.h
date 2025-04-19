#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Button.h"
#include <vector>
#include <string>

class GameOverScreen
{
private:
	TTF_Font* font;
	SDL_Rect rect;
	SDL_Texture* backgroundTexture;
	int currentScore = 0;
	std::vector<int> highScores;

	Button restartButton;
	Button exitButton;

	void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, bool centerd = false);
public:
	GameOverScreen(SDL_Renderer* ren);
	~GameOverScreen();

	void setScore(int score);
	void setHighScores(const std::vector<int>& scores);
	void Render(SDL_Renderer* renderer);
	void handleEvent(SDL_Event& event, bool& restartRequested, bool& exitRequested);
};