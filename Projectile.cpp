#include "Projectile.h"
#include <SDL_image.h>

Projectile::Projectile() 
{
    active = false;
    speed = 5.0f;
    x_pos = 0;
    y_pos = 0;
    facingRight = true;//
    for (int i = 0; i < 6; ++i) {
        spriteClips[i] = { 0, 0, 0, 0 };
    }
    setSrc(0, 0, 160, 240);
    setDest(0, 0, 160, 240);
}

void Projectile::setSpriteSheet(SDL_Renderer* ren, const char* address)
{
    spritesheet = IMG_LoadTexture(ren, address);
    for (int i = 0; i < 6; i++)
    {
        spriteClips[i].x = i * getDest().w;
        spriteClips[i].y = 0;
        spriteClips[i].w = getDest().w;
        spriteClips[i].h = getDest().h;
    }
}

void Projectile::setDirection(bool right)
{
    facingRight = right;
}

void Projectile::Update(Character character) {
    if (!active && character.getAttackState()) {
        active = true;
        facingRight = character.getDirection();
        if (facingRight) {
            x_pos = character.getRect().x + 90;
            y_pos = character.getRect().y - 50;
        }
        else
        {
            x_pos = character.getRect().x - 60;
            y_pos = character.getRect().y - 50;
        }
        setDest(x_pos, y_pos, 100, 150);
    }

    if (active)
    {
        if (facingRight) {
            x_pos += speed;
        }
        else {
            x_pos -= 1.5 * speed;
        }

        setDest(x_pos, y_pos, 100, 150);

        
        if (currFrame >= 5 || x_pos < -100 || x_pos > 1900) {
            active = false;
            currFrame = 0;
        }
        if (animationTimer++ >= 10) // > attack animaitonTimer
        {
            animationTimer = 0;
            if (++currFrame >= 6)
            {
               active = false;
               currFrame = 0;
            }
        }
    }

    proj_Rect.x = x_pos;
    proj_Rect.y = y_pos;
    proj_Rect.w = getDest().w;
    proj_Rect.h = getDest().h;


    if (!character.isAlive()) {
        active = false;
    }
}

void Projectile::Render(SDL_Renderer* ren) {
    if (active) {
        SDL_Rect* currentClip = &spriteClips[currFrame];
        SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(ren, spritesheet, currentClip, &getDest(), 0, NULL, flip);
    }
}