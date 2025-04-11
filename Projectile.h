#pragma once
#include "Object.h"
#include "Character.h"

class Projectile : public Object {
public:
    Projectile();
    void Update(Character character);
    void Render(SDL_Renderer* ren) override; 
    bool isActive() const { return active; }
    void setSpeed(float spd) { speed = spd; }
    void setActive(bool act) { active = act; }
    void setDirection(bool right);
    void setSpriteSheet(SDL_Renderer* ren, const char* address);
    SDL_Rect getRect() const { return proj_Rect; }


private:
    float x_pos, y_pos;
    float speed; 
    SDL_Texture* spritesheet = NULL;
    SDL_Rect spriteClips[6];
    int currFrame = 0;
    int animationTimer = 0;
    bool facingRight; 
    bool active = false;
    SDL_Rect proj_Rect;
};