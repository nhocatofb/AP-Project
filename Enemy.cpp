#include "Enemy.h"

void Enemy::create(SDL_Renderer *renderer) {
        SDL_Surface* surface = SDL_LoadBMP("img/enemy.bmp");
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
        desRect.x = 0;
        desRect.y = 0;
        sourceRect.x = 0;
        sourceRect.y = 0;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
}

void Enemy::render(SDL_Renderer *renderer) {
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

string Enemy::canMove() {
    if(desRect.x<SCREEN_WIDTH) return "canMoveRight";
    if(desRect.y>0)            return "canMoveUp";
    if(desRect.x>0)            return "canMoveLeft";
    if(desRect.y<SCREEN_HEIGHT)return "canMoveDown";
}

void Enemy::move() {
    if(canMove()=="canMoveRight") moveRight();
    else if (canMove()=="canMoveUp") moveUp();
    else if (canMove()=="canMoveLeft") moveLeft();
    else moveDown();
    desRect.x += stepX*10;
    desRect.y += stepY*10;
}

void Enemy::moveRight() {
        stepX=1;
        stepY=0;
}
void Enemy::moveLeft() {
        stepX=-1;
        stepY=0;
}
void Enemy::moveUp() {
        stepX=0;
        stepY=-1;
}
void Enemy::moveDown() {
        stepX=0;
        stepY=1;
}

bool Enemy::inside(int minX, int minY, int maxX, int maxY) {
    return (desRect.x>=minX && desRect.y>=minY && desRect.x+desRect.w<=maxX && desRect.y+desRect.h<=maxY);
}

