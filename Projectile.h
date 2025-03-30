#pragma once
#include "Object.h"
#include "Character.h"

class Projectile : public Object {
public:
    Projectile();
    void Update(Character player);
    void Render(SDL_Renderer* ren) override; 
    bool isActive() const { return active; }
    void setActive() { active = true; }
    void setDirection(bool right);
    void setSpriteSheet(SDL_Renderer* ren);

private:
    float x_pos, y_pos;
    float speed; 
    SDL_Texture* spritesheet = NULL;
    SDL_Rect spriteClips[5];
    int currFrame = 0;
    int animationTimer = 0;
    bool facingRight; 
    bool active;
};