#include "Bomb.h"

void Bomb::create(SDL_Renderer *renderer,int _x, int _y) {
        SDL_Surface* surface = SDL_LoadBMP("img/bomb.bmp");
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
        desRect.x = _x;
        desRect.y = _y;
        sourceRect.x = 0;
        sourceRect.y = 0;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
}

void Bomb::render(SDL_Renderer *renderer) {
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}
