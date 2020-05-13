#include "Enemy.h"

void Enemy::create(SDL_Renderer *renderer) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    desRect.x = 1160;
    desRect.y = rand()%500+1;
    for(int i=0; i<ENEMY_FRAMES; i++) {
        clips[i].x = sourceRect.w*i/ENEMY_FRAMES;
        clips[i].y = 0;
        clips[i].w = sourceRect.w/ENEMY_FRAMES;
        clips[i].h = sourceRect.h;
    }
    explode.create(renderer);
}

void Enemy::render(SDL_Renderer *renderer) {
    if(alive==false) {
        desRect.w =0;
        desRect.h =0;
        explode.render(renderer, desRect.x, desRect.y);
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

void Enemy::randomNumber() {
    if(rdNumber<10) rdNumber = rand() % 20 + 1;
    else if(rdNumber>20 && rdNumber<40) rdNumber = rand()%20+20 +1;
    else if(rdNumber>40 && rdNumber<60) rdNumber = rand()%20+40 +1;
    else if(rdNumber>60 && rdNumber<80) rdNumber = rand()%20+60 +1;
    else rdNumber = rand() % 80 + 1;
}

void Enemy::move() {
    if(alive==false) return;
    randomNumber();
    if(rdNumber%5==0) speed =1.5;
    else if(rdNumber%5==1) speed = 0.5;
    else speed = 1;

    if(rdNumber <= 20 && inside()==true) moveRight();
    else if (rdNumber <= 40 && inside()==true) moveUp();
    else if (rdNumber <= 60 && inside()==true) moveLeft();
    else if (rdNumber <= 80 && inside()==true) moveDown();
    desRect.x += stepX;
    desRect.y += stepY;
    if(inside()==false) moveBack();
}

void Enemy::moveRight() {
        stepX=2*speed;
        stepY=0;
        just_move = "right";
}
void Enemy::moveLeft() {
        stepX= -2*speed;
        stepY=0;
        just_move = "left";
}
void Enemy::moveUp() {
        stepX=0;
        stepY=-2*speed;
        just_move = "up";
}
void Enemy::moveDown() {
        stepX=0;
        stepY=2*speed;
        just_move = "down";
}

void Enemy::moveBack() {
    if(just_move=="right") moveLeft();
    else if(just_move=="left") moveRight();
    else if(just_move=="up") moveDown();
    else if(just_move=="down") moveUp();
    desRect.x += stepX;
    desRect.y += stepY;
    rdNumber = rand() % 80 + 1;
}

bool Enemy::inside() {
    return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
}

