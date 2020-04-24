#include "Bomb.h"

void Bomb::create(SDL_Renderer *renderer,int _x, int _y) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    desRect.x = _x;
    desRect.y = _y;
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = sourceRect.w/4;
    clips[0].h = sourceRect.h;

    clips[1].x = sourceRect.w/4;
    clips[1].y = 0;
    clips[1].w = sourceRect.w/4;
    clips[1].h = sourceRect.h;

    clips[2].x = sourceRect.w/2;
    clips[2].y = 0;
    clips[2].w = sourceRect.w/4;
    clips[2].h = sourceRect.h;

    clips[3].x = sourceRect.w*3/4;
    clips[3].y = 0;
    clips[3].w = sourceRect.w/4;
    clips[3].h = sourceRect.h;
}

void Bomb::render(SDL_Renderer *renderer) {
    sourceRect.x = clips[frame/5].x;
    sourceRect.y = clips[frame/5].y;
    sourceRect.h = clips[frame/5].h;
    sourceRect.w = clips[frame/5].w;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
    frame++;
    if(frame/5 >= BOMB_FRAMES) frame =0;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}
