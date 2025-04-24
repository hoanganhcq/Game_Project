#include "Button.h"

Button::Button() : buttonRect({ 0, 0, 0, 0 }), buttonTexture(NULL), pressedTexure(NULL) {}

Button::Button(int x, int y, int w, int h, SDL_Texture* tex)
	: buttonRect({ x, y, w, h }), originalRect({ x, y, w, h }), buttonTexture(tex), pressedTexure(NULL) {
}

void Button::Render(SDL_Renderer* ren)
{
	SDL_Texture* tex = hovering ? hoverTexture : buttonTexture;
	if (pressedTexure && isPressed)
		tex = pressedTexure;

	if (tex)
		SDL_RenderCopy(ren, tex, NULL, &buttonRect);

	if (isPressed)
	{

		SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 60);
		SDL_RenderFillRect(ren, &buttonRect);


		SDL_SetRenderDrawColor(ren, 255, 215, 0, 255);
		SDL_RenderDrawRect(ren, &buttonRect);
	}
}

bool Button::isHovering(int mouseX, int mouseY) const
{
	return (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
		mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);
}

void Button::setRect(int x, int y, int w, int h)
{
	buttonRect = { x, y, w, h };
	originalRect = buttonRect;
}

void Button::loadTexture(const char* fileLocation, SDL_Renderer* ren)
{
	buttonTexture = TextureManager::Texture(fileLocation, ren);
}

void Button::loadHoverTexure(const char* fileLocation, SDL_Renderer* ren) 
{
	hoverTexture = TextureManager::Texture(fileLocation, ren);
}

void Button::setPressedTexture(const char* fileLocation, SDL_Renderer* ren)
{
	pressedTexure = TextureManager::Texture(fileLocation, ren);
}

void Button::setPressed(bool pressed)
{
	if (pressed && !isPressed)
	{
		isPressed = true;
		buttonRect.x += 2;
		buttonRect.y += 2;
		buttonRect.w -= 4;
		buttonRect.h -= 4;
	}
	else if (!pressed && isPressed)
	{
		isPressed = false;
		buttonRect = originalRect;
	}
}

bool Button::getPressed() const
{
	return isPressed;
}

SDL_Rect Button::getRect()
{
	return buttonRect;
}

bool Button::isReadyToClick()
{
	Uint32 current = SDL_GetTicks();
	if (current - lastClickTime >= clickDelay)
	{
		lastClickTime = current;
		return true;
	}
	return false;
}
