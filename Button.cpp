#include "Button.h"

Button::Button() : buttonRect({ 0, 0, 0, 0 }), buttonTexture(NULL) {}

Button::Button(int x, int y, int w, int h, SDL_Texture* tex)
    : buttonRect({ x, y, w, h }), buttonTexture(tex) {
}

void Button::Render(SDL_Renderer* ren)
{
    if (buttonTexture) {
        SDL_RenderCopy(ren, buttonTexture, NULL, &buttonRect);
    }
}

bool Button::isHovering(int mouseX, int mouseY) const 
{
    return (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);
}

void Button::setRect(int x, int y, int w, int h)
{
    buttonRect.x = x;
    buttonRect.y = y;
    buttonRect.w = w;
    buttonRect.h = h;
}

void Button::loadTexture(const char* fileLocation, SDL_Renderer* ren)
{
    buttonTexture = TextureManager::Texture(fileLocation, ren);
}

SDL_Rect Button::getRect() 
{
    return buttonRect;
}

bool Button::isReadyToClick() {
    Uint32 current = SDL_GetTicks();
    if (current - lastClickTime >= clickDelay) {
        lastClickTime = current;
        return true;
    }
    return false;
}
