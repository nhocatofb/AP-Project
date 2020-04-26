#include "Enemy.h"

void Enemy::create(SDL_Renderer *renderer) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    desRect.x = SCREEN_WIDTH/2;
    desRect.y = SCREEN_HEIGHT/2;
    for(int i=0; i<ENEMY_FRAMES; i++) {
        clips[i].x = sourceRect.w*i/ENEMY_FRAMES;
        clips[i].y = 0;
        clips[i].w = sourceRect.w/ENEMY_FRAMES;
        clips[i].h = sourceRect.h;
    }
}

void Enemy::render(SDL_Renderer *renderer) {
    sourceRect.x = clips[frame/20].x;
    sourceRect.y = clips[frame/20].y;
    sourceRect.h = clips[frame/20].h;
    sourceRect.w = clips[frame/20].w;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
    frame++;
    if(frame/20 >= ENEMY_FRAMES) frame =0;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

int Enemy::randomNumber() {
    return rand() % 4;
}

void Enemy::move() {
    if(randomNumber() == 0 && inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)==true) moveRight();
    else if (randomNumber() == 1 && inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)==true) moveUp();
    else if (randomNumber() == 2 && inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)==true) moveLeft();
    else if (randomNumber() == 3 && inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)==true) moveDown();
    desRect.x += stepX;
    desRect.y += stepY;
}

void Enemy::moveRight() {
        stepX=2;
        stepY=0;
}
void Enemy::moveLeft() {
        stepX= -2;
        stepY=0;
}
void Enemy::moveUp() {
        stepX=0;
        stepY=-2;
}
void Enemy::moveDown() {
        stepX=0;
        stepY=2;
}

bool Enemy::inside(int minX, int minY, int maxX, int maxY) {
    return (desRect.x>=minX && desRect.y>=minY && desRect.x+desRect.w<=maxX && desRect.y+desRect.h<=maxY);
}

