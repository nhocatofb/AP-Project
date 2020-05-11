#include "bullet.h"

#include "player.h"

void Bullet::create(SDL_Renderer *renderer, int _x, int _y) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    sourceRect.w /=4;
    desRect.x = _x;
    desRect.y = _y;
    sourceRect.x =0;
    sourceRect.y =0;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
    explode.create(renderer);
}


void Bullet::render(SDL_Renderer *renderer) {
    if(destroy==true) {
        desRect.w =0;
        desRect.h =0;
        explode.render(renderer, desRect.x, desRect.y);
        return;
    }
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    move();
}

void Bullet::move() {
    desRect.x += stepX;
    desRect.y += stepY;
    if(inside()==false) moveBack();
}

void Bullet::moveRight() {
    stepX = 10;
    stepY = 0;
    just_move = "right";
}
void Bullet::moveLeft() {
    stepX = -10;
    stepY = 0;
    just_move = "left";
}
void Bullet::moveUp() {
    stepX = 0;
    stepY = -10;
    just_move = "up";
}
void Bullet::moveDown() {
    stepX = 0;
    stepY = 10;
    just_move = "down";
}

bool Bullet::inside() {
    return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
}

void Bullet::moveBack() {
    if(just_move=="right") moveLeft();
    else if(just_move=="left") moveRight();
    else if(just_move=="up") moveDown();
    else if(just_move=="down") moveUp();
}
