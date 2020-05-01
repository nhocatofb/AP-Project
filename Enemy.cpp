#include "Enemy.h"

Enemy::Enemy(SDL_Renderer *renderer) {
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
    if(alive==false) {
        SDL_DestroyTexture(texture);
        return;
    }
    sourceRect.x = clips[frame/20].x;
    sourceRect.y = clips[frame/20].y;
    sourceRect.h = clips[frame/20].h;
    sourceRect.w = clips[frame/20].w;
    desRect.w = sourceRect.w*4/5;
    desRect.h = sourceRect.h*4/5;
    frame++;
    if(frame/20 >= ENEMY_FRAMES) frame =0;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

int Enemy::randomNumber() {
    if(rdNumber<50-2) rdNumber = rand() % 50 + 1;
    else if(rdNumber>50 && rdNumber<100) rdNumber = rand()%50+50 +1;
    else if(rdNumber>100 && rdNumber<150) rdNumber = rand()%50+100 +1;
    else if(rdNumber>150 && rdNumber<200) rdNumber = rand()%50+150 +1;
    else rdNumber = rand() % 200 + 1;
    return rdNumber;
}

void Enemy::move() {
    if(randomNumber() <= 50 && inside()==true) moveRight();
    else if (randomNumber() <= 100 && inside()==true) moveUp();
    else if (randomNumber() <= 150 && inside()==true) moveLeft();
    else if (randomNumber() <= 200 && inside()==true) moveDown();
    desRect.x += stepX;
    desRect.y += stepY;
    if(inside()==false) {
        moveBack();
        rdNumber = rand() % 200 + 1;
    }
}

void Enemy::moveRight() {
        stepX=2;
        stepY=0;
        just_move = "right";
}
void Enemy::moveLeft() {
        stepX= -2;
        stepY=0;
        just_move = "left";
}
void Enemy::moveUp() {
        stepX=0;
        stepY=-2;
        just_move = "up";
}
void Enemy::moveDown() {
        stepX=0;
        stepY=2;
        just_move = "down";
}

void Enemy::moveBack() {
    if(just_move=="right") moveLeft();
    else if(just_move=="left") moveRight();
    else if(just_move=="up") moveDown();
    else if(just_move=="down")  moveUp();
}

bool Enemy::inside() {
    return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
}

