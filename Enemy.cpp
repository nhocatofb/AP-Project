#include "Enemy.h"

void Enemy::create(SDL_Renderer *renderer) {
        SDL_Surface* surface = SDL_LoadBMP("img/enemy.bmp");
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
        desRect.x = SCREEN_WIDTH/2;
        desRect.y = SCREEN_HEIGHT/2;
        sourceRect.x = 0;
        sourceRect.y = 0;
        desRect.w = sourceRect.w*2;
        desRect.h = sourceRect.h*2;
}

void Enemy::render(SDL_Renderer *renderer) {
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

int Enemy::randomNumber() {
    srand(time(0));
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

