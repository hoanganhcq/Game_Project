#include "GameOverScreen.h"
#include <SDL_image.h>
#include <algorithm>

GameOverScreen::GameOverScreen(SDL_Renderer* ren)
{
    TTF_Init();
    rect = { 550, -50, 700, 1050 };
    font = TTF_OpenFont("assets/truetype_font/Poppins-Bold.ttf", 40);
	backgroundTexture = IMG_LoadTexture(ren, "assets/image/gameOver_NoScores.png");

    restartButton.loadTexture("assets/image/gameOver_restartButton.png", ren);
    restartButton.loadHoverTexure("assets/image/gameOver_restartButtonHovering.png", ren);
    restartButton.setRect(650, 850, 200, 100);
    exitButton.loadTexture("assets/image/gameOver_exitButton.png", ren);
    exitButton.loadHoverTexure("assets/image/gameOver_exitButtonHovering.png", ren);
    exitButton.setRect(950, 850, 200, 100);

    gameOverMusic = Mix_LoadMUS("assets/audio/gameOver_music.mp3");
    pressed_sound = Mix_LoadWAV("assets/audio/button_pressed.wav");
}

void GameOverScreen::setScore(int score) {
    currentScore = score;
}

void GameOverScreen::setHighScores(const std::vector<int>& scores) {
    highScores = scores;
    std::sort(highScores.rbegin(), highScores.rend());
    if (highScores.size() > 5) highScores.resize(5);
}

void GameOverScreen::renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, bool centered) {
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

void GameOverScreen::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &rect);

    // Current Score
    SDL_Color white = { 255, 255, 255 };
    renderText(renderer, "YOUR SCORE: " + std::to_string(currentScore), 900, 300, white, true);

    // High Scores
    SDL_Color yellow = { 255, 215, 0 };
    renderText(renderer, "TOP 5 HIGH SCORES", 900, 400, yellow, true);

    for (size_t i = 0; i < highScores.size(); ++i) {
        std::string line = std::to_string(highScores[i]);
        renderText(renderer, line, 850, 485 + i * 56, white, true);
    }

    restartButton.Render(renderer);
    exitButton.Render(renderer);
}

void GameOverScreen::handleEvent(SDL_Event& event, bool& restartRequested, bool& exitRequested)
{
    if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;
        
        if (restartButton.isHovering(x, y)) {
            restartButton.setHover(true);
        }
        else restartButton.setHover(false);

        if (exitButton.isHovering(x, y)) {
            exitButton.setHover(true);
        }
        else exitButton.setHover(false);
    }


    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int mx = event.button.x;
        int my = event.button.y;

        if (restartButton.isHovering(mx, my)) {
            restartRequested = true;
            Mix_PlayChannel(0, pressed_sound, 0);
        }

        if (exitButton.isHovering(mx, my)) {
            exitRequested = true;
            Mix_PlayChannel(0, pressed_sound, 0);
        }
    }
}