#include "bullet.h"

#include "player.h"

void Bullet::create(SDL_Renderer *renderer, int _x, int _y) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    desRect.x = _x;
    desRect.y = _y;

    clips[0].x = 0;
    clips[1].x = sourceRect.w / 2;
    clips[0].y = clips[1].y = 0;
    clips[0].w = clips[1].w = sourceRect.w / 2;
    clips[0].h = clips[1].h = sourceRect.h;
    explode.create(renderer);
}


void Bullet::render(SDL_Renderer *renderer) {
    if(destroy==true) {
        desRect.w =0;
        desRect.h =0;
        explode.render(renderer, desRect.x, desRect.y);
        return;
    }
    sourceRect.x = clips[frame/2].x;
    sourceRect.y = clips[frame/2].y;
    desRect.w = sourceRect.w = clips[frame/2].w;
    desRect.h = sourceRect.h = clips[frame/2].h;
    frame++;
    if (frame/2 == frames) frame = 0;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    move();
}

void Bullet::move() {
    desRect.x += stepX;
    desRect.y += stepY;
}

void Bullet::moveRight() {
    stepX = 7;
    stepY = 0;
    just_move = "right";
}
void Bullet::moveLeft() {
    stepX = -7;
    stepY = 0;
    just_move = "left";
}
void Bullet::moveUp() {
    stepX = 0;
    stepY = -7;
    just_move = "up";
}
void Bullet::moveDown() {
    stepX = 0;
    stepY = 7;
    just_move = "down";
}

bool Bullet::inside() {
    return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
}

