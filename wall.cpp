#include "player.h"

void Wall::create(SDL_Renderer *renderer, int _x, int _y) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    for (int i = 0; i < frames; i++) {
        clips[i].x = sourceRect.w * i / frames;
        clips[i].y = 0;
        clips[i].w = sourceRect.w / frames;
        clips[i].h = sourceRect.h;
    }

    desRect.x = _x;
    desRect.y = _y;
    explode.create(renderer);
}

void Wall::render(SDL_Renderer *renderer) {
    if(destroy==true || frame == frames) {
        desRect.w =0;
        desRect.h =0;
        explode.render(renderer, desRect.x, desRect.y);
        return;
    }
    sourceRect.x = clips[frame].x;
    sourceRect.y = clips[frame].y;
    sourceRect.w = clips[frame].w;
    sourceRect.h = clips[frame].h;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}
