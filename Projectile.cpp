#include "Projectile.h"
#include <SDL_image.h>

Projectile::Projectile() {
    active = false;
    speed = 5.0f;
    x_pos = 0;
    y_pos = 0;
    facingRight = true;//
    setSrc(0, 0, 160, 240);
    setDest(0, 0, 160, 240);
}

void Projectile::setSpriteSheet(SDL_Renderer* ren)
{
    spritesheet = IMG_LoadTexture(ren, "assets/image/energy_attack_1.png");
    for (int i = 0; i < 5; i++)
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

void Projectile::Update(Character player) {
    if (!active && player.getAttackState()) {
        active = true;
        facingRight = player.getDirection();
        if (facingRight) {
            x_pos = player.getRect().x + 90;
            y_pos = player.getRect().y - 50;
        }
        else
        {
            x_pos = player.getRect().x - 60;
            y_pos = player.getRect().y - 50;
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
        if (animationTimer++ >= 12) // > attack animaitonTimer
        {
            animationTimer = 0;
            if (++currFrame >= 5)
            {
               active = false;
               currFrame = 0;
            }
        }
    }
}

void Projectile::Render(SDL_Renderer* ren) {
    if (active) {
        SDL_Rect* currentClip = &spriteClips[currFrame];
        SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(ren, spritesheet, currentClip, &getDest(), 0, NULL, flip);
    }
}