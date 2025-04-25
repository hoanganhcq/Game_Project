#include "PauseContainer.h"
#include "TextureManager.h"

PauseContainer::PauseContainer() {
    containerRect = { 0, 0, 0, 0 };
    pressed_sound = Mix_LoadWAV("assets/audio/button_pressed.wav");
}

void PauseContainer::setRect(int x, int y, int w, int h) {
    containerRect = { x, y, w, h };
}

void PauseContainer::loadTexture(SDL_Renderer* ren) {
    containerTexture = TextureManager::Texture("assets/image/pause_container.png", ren);
}

void PauseContainer::loadButtons(SDL_Renderer* ren) {
    resumeButton.loadTexture("assets/image/button_container.png", ren);
    resumeButton.loadHoverTexure("assets/image/button_containerHovering.png", ren);
    exitButton.loadTexture("assets/image/button_container.png", ren);
    exitButton.loadHoverTexure("assets/image/button_containerHovering.png", ren);

    int buttonW = 180, buttonH = 100;
    resumeButton.setRect(containerRect.x + containerRect.w / 2 - buttonW - 20,
        containerRect.y + containerRect.h / 2 - buttonH / 2,
        buttonW, buttonH);
    exitButton.setRect(containerRect.x + containerRect.w / 2 + 20,
        containerRect.y + containerRect.h / 2 - buttonH / 2,
        buttonW, buttonH);
}

void PauseContainer::loadTexts(SDL_Renderer* ren, TTF_Font* font) {
    SDL_Color color = { 255, 215, 0, 255 }; // light yellow

    SDL_Surface* resumeSurface = TTF_RenderText_Solid(font, "Resume", color);
    SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", color);

    resumeTextTex = SDL_CreateTextureFromSurface(ren, resumeSurface);
    exitTextTex = SDL_CreateTextureFromSurface(ren, exitSurface);

    resumeTextRect = {
        resumeButton.getRect().x + (resumeButton.getRect().w - resumeSurface->w) / 2,
        resumeButton.getRect().y + (resumeButton.getRect().h - resumeSurface->h) / 2,
        resumeSurface->w,
        resumeSurface->h
    };

    exitTextRect = {
        exitButton.getRect().x + (exitButton.getRect().w - exitSurface->w) / 2,
        exitButton.getRect().y + (exitButton.getRect().h - exitSurface->h) / 2,
        exitSurface->w,
        exitSurface->h
    };

    SDL_FreeSurface(resumeSurface);
    SDL_FreeSurface(exitSurface);
}

void PauseContainer::handleEvent(SDL_Event& event, bool& resumeRequested, bool& exitRequested)
{
    if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;
        if (resumeButton.isHovering(x, y)) {
            resumeButton.setHover(true);
        }
        else resumeButton.setHover(false);

        if (exitButton.isHovering(x, y)) {
            exitButton.setHover(true);
        }
        else exitButton.setHover(false);
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int mx = event.button.x;
        int my = event.button.y;

        if (resumeButton.isHovering(mx, my)) {
            resumeRequested = true;
            Mix_PlayChannel(0, pressed_sound, 0);
        }

        if (exitButton.isHovering(mx, my)) {
            exitRequested = true;
            Mix_PlayChannel(0, pressed_sound, 0);
        }
    }
}

void PauseContainer::Render(SDL_Renderer* ren) {
    if (containerTexture) {
        SDL_RenderCopy(ren, containerTexture, NULL, &containerRect);
    }
    resumeButton.Render(ren);
    exitButton.Render(ren);

    if (resumeTextTex) SDL_RenderCopy(ren, resumeTextTex, NULL, &resumeTextRect);
    if (exitTextTex) SDL_RenderCopy(ren, exitTextTex, NULL, &exitTextRect);
}