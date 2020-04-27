#include "wall.h"

Wall::Wall(SDL_Renderer *renderer) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    sourceRect.w/=4;
    desRect.x = 0;
    desRect.y = 0;
    sourceRect.x =0;
    sourceRect.y =0;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
}

void Wall::render(SDL_Renderer *renderer) {
    for(int i=0; i<SCREEN_HEIGHT/sourceRect.h; i++) {
        desRect.y = i*sourceRect.h;
        desRect.x = 0;
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    }
    for(int i=1; i<SCREEN_WIDTH/sourceRect.w; i++) {
        desRect.x = i*sourceRect.w;
        desRect.y = 0;
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    }
    for(int i=1; i<SCREEN_HEIGHT/sourceRect.h; i++) {
        desRect.x = SCREEN_WIDTH - sourceRect.w;
        desRect.y = i*sourceRect.h;
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    }
    for(int i=1; i<SCREEN_WIDTH/sourceRect.w-1; i++) {
        desRect.x = i*sourceRect.w;
        desRect.y = SCREEN_HEIGHT - sourceRect.h;
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    }
}
