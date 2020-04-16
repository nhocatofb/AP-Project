#include "player.h"

void Player::loadTexture(string path, SDL_Renderer *renderer) {
        SDL_Surface* surface = SDL_LoadBMP(path.c_str());
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
        sourceRect.x = desRect.x = 0;
        sourceRect.y = desRect.y = 0;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
}

void Player::render(SDL_Renderer *renderer) {
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

void Player::moveRight() {
        desRect.x +=20;
}
void Player::moveLeft() {
        desRect.x -=20;
}
void Player::moveUp() {
        desRect.y -=20;
}
void Player::moveDown() {
        desRect.y +=20;
}

bool Player::inside(int minX, int minY, int maxX, int maxY) {
    return (desRect.x>=minX && desRect.y>=minY && desRect.x+desRect.w<=maxX && desRect.y+desRect.h<=maxY);
}

void Player::createBomb(SDL_Renderer *renderer) {
    bomb.create(renderer, desRect.x, desRect.y);
}

void Player::event(SDL_Window *window, SDL_Renderer* renderer){
    SDL_Event e;
    if(SDL_PollEvent(&e)==0) {};
    if(e.type == SDL_QUIT) quitSDL(window, renderer);
    if(e.type==SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE: break;
        case SDLK_LEFT: moveLeft(); break;
        case SDLK_RIGHT: moveRight(); break;
        case SDLK_UP: moveUp(); break;
        case SDLK_DOWN: moveDown(); break;
        case SDLK_SPACE: createBomb(renderer); break;
        default: break;
        }
    }
}
