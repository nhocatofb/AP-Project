#include "Bomb.h"

void Bomb::create(SDL_Renderer *renderer,int _x, int _y) {
    SDL_Surface* surface = SDL_LoadBMP(BombIMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);

    surface = SDL_LoadBMP(ExplodeIMG.c_str());
    colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    explode_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(explode_texture, nullptr, nullptr, &explode_sourceRect.w, &explode_sourceRect.h);

    for(int i=0; i<BOMB_FRAMES; i++) {
        clips[i].x = sourceRect.w*i/BOMB_FRAMES;
        clips[i].y = 0;
        clips[i].w = sourceRect.w/BOMB_FRAMES;
        clips[i].h = sourceRect.h;
    }

    for(int i=0; i<EXPLODE_FRAMES_H; i++) {
        for(int j=0; j<EXPLODE_FRAMES_W; j++) {
            explode_clips[i][j].x = explode_sourceRect.w*j/EXPLODE_FRAMES_W;
            explode_clips[i][j].y = explode_sourceRect.h*i/EXPLODE_FRAMES_H;
            explode_clips[i][j].w = explode_sourceRect.w/EXPLODE_FRAMES_W;
            explode_clips[i][j].h = explode_sourceRect.h/EXPLODE_FRAMES_H;
        }
    }

    desRect.x = _x;
    desRect.y = _y;
    isCreate = true;
    timeToExplode = 40;
}

void Bomb::render(SDL_Renderer *renderer) {
    if(frame/10 >= BOMB_FRAMES) frame =0;
    if(timeToExplode<=0) {
        explode(renderer);
        frame++;
        return;
    }
    sourceRect.x = clips[frame/10].x;
    sourceRect.y = clips[frame/10].y;
    sourceRect.h = clips[frame/10].h;
    sourceRect.w = clips[frame/10].w;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
    frame++;
    if(isCreate==true) timeToExplode--;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
}

void Bomb::explode(SDL_Renderer *renderer) {
    for(int i=0; i<5; i++) {
        explode_sourceRect.x = explode_clips[i][frame/10].x;
        explode_sourceRect.y = explode_clips[i][frame/10].y;
        explode_sourceRect.h = explode_clips[i][frame/10].h;
        explode_sourceRect.w = explode_clips[i][frame/10].w;
        explode_desRect.w = explode_sourceRect.w;
        explode_desRect.h = explode_sourceRect.h;
        switch(i) {
            case 0: {
                explode_desRect.x = desRect.x;
                explode_desRect.y = desRect.y;
                break;
            }
            case 1: {
                explode_desRect.x = desRect.x;
                explode_desRect.y = desRect.y-explode_desRect.h;
                break;
            }
            case 2: {
                explode_desRect.x = desRect.x-desRect.w;
                explode_desRect.y = desRect.y;
                break;
            }
            case 3: {
                explode_desRect.x = desRect.x+desRect.w;
                explode_desRect.y = desRect.y;
                break;
            }
            case 4: {
                explode_desRect.x = desRect.x;
                explode_desRect.y = desRect.y+explode_desRect.h;
                break;
            }
        }
        SDL_RenderCopy(renderer, explode_texture, &explode_sourceRect, &explode_desRect);
    }
}
