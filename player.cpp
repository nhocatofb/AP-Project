#include "player.h"

Player::Player(string path, SDL_Renderer *renderer) {
        SDL_Surface* surface = SDL_LoadBMP(path.c_str());
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
        desRect.x = firstX;
        desRect.y = firstY;
        sourceRect.x = 0;
        sourceRect.y = 0;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
}

void Player::render(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

void Player::moveRight() {
    just_move = "right";
    desRect.x +=stepX;
}
void Player::moveLeft() {
    just_move = "left";
    desRect.x -=stepX;
}
void Player::moveUp() {
    just_move = "up";
    desRect.y -=stepY;
}
void Player::moveDown() {
    just_move = "down";
    desRect.y +=stepY;
}

void Player::moveBack() {
    if(just_move=="right") moveLeft();
    else if(just_move=="left") moveRight();
    else if(just_move=="up") moveDown();
    else if(just_move=="down")  moveUp();
    else ;
}

void Player::createBomb(SDL_Renderer *renderer) {
    bomb.create(renderer, desRect.x, desRect.y);
}

void Player::createWall_top(SDL_Renderer *renderer) {
    wall[number_of_wall_created].create(renderer, desRect.x, desRect.y-wall[0].desRect.h-1);
    number_of_wall_created++;
}

void Player::createWall_bot(SDL_Renderer *renderer) {
    wall[number_of_wall_created].create(renderer, desRect.x, desRect.y+desRect.h+1);
    number_of_wall_created++;
}

void Player::createWall_left(SDL_Renderer *renderer) {
    wall[number_of_wall_created].create(renderer, desRect.x-wall[0].desRect.w-1, desRect.y);
    number_of_wall_created++;
}

void Player::createWall_rigth(SDL_Renderer *renderer) {
    wall[number_of_wall_created].create(renderer, desRect.x+desRect.w+1, desRect.y);
    number_of_wall_created++;
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
        case SDLK_w: createWall_top(renderer); break;
        case SDLK_a: createWall_left(renderer); break;
        case SDLK_d: createWall_rigth(renderer); break;
        case SDLK_s: createWall_bot(renderer); break;
        default: break;
        }
    }
}

