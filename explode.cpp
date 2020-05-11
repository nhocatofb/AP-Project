#include "explode.h"

void Explode::create(SDL_Renderer *renderer) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    chunk = Mix_LoadWAV("audio/Explosion+3.wav");

    for(int i=0; i<FRAMES_H; i++) {
        for(int j=0; j<FRAMES_W; j++) {
            clips[i][j].x = sourceRect.w*j/FRAMES_W;
            clips[i][j].y = sourceRect.h*i/FRAMES_H;
            clips[i][j].w = sourceRect.w/FRAMES_W;
            clips[i][j].h = sourceRect.h/FRAMES_H;
        }
    }
    desRect.x = desRect.y = desRect.w = desRect.h =0;
}

void Explode::render(SDL_Renderer *renderer, int _x, int _y) {
    if(frame/10==FRAMES_W) {
        desRect.w = desRect.h = sourceRect.h = sourceRect.w =0;
        return;
    }
    Mix_PlayChannel(-1, chunk, 0);
    exploded = true;
    for(int i=0; i<5; i++) {
        sourceRect.x = clips[i][frame/10].x;
        sourceRect.y = clips[i][frame/10].y;
        sourceRect.h = clips[i][frame/10].h;
        sourceRect.w = clips[i][frame/10].w;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
        switch(i) {
            case 0: {
                desRect.x = _x;
                desRect.y = _y;
                break;
            }
            case 1: {
                desRect.x = _x;
                desRect.y = _y-desRect.h;
                break;
            }
            case 2: {
                desRect.x = _x-desRect.w;
                desRect.y = _y;
                break;
            }
            case 3: {
                desRect.x = _x+desRect.w;
                desRect.y = _y;
                break;
            }
            case 4: {
                desRect.x = _x;
                desRect.y = _y+desRect.h;
                break;
            }
        }
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    }
    frame++;
}

bool Explode::destroy(SDL_Rect a, int _x, int _y) {
    if(frame/10==FRAMES_W) return false;
    if(exploded==false) return false;
    for(int i=0; i<5; i++) {
        sourceRect.x = clips[i][frame/10].x;
        sourceRect.y = clips[i][frame/10].y;
        sourceRect.h = clips[i][frame/10].h;
        sourceRect.w = clips[i][frame/10].w;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
        switch(i) {
            case 0: {
                desRect.x = _x;
                desRect.y = _y;
                break;
            }
            case 1: {
                desRect.x = _x;
                desRect.y = _y-desRect.h;
                break;
            }
            case 2: {
                desRect.x = _x-desRect.w;
                desRect.y = _y;
                break;
            }
            case 3: {
                desRect.x = _x+desRect.w;
                desRect.y = _y;
                break;
            }
            case 4: {
                desRect.x = _x;
                desRect.y = _y+desRect.h;
                break;
            }
        }
        if(impact(a, desRect)==true) return true;
    }
    return false;
}


