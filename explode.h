#ifndef EXPLODE_H
#define EXPLODE_H

#include "SDL_utils.h"

struct Explode {
    SDL_Rect sourceRect, desRect;
    SDL_Texture* texture= nullptr;
    Mix_Chunk* chunk = nullptr;

    const string IMG = "img/explode.bmp";

    static const int FRAMES_H = 7, FRAMES_W = 4;
    SDL_Rect clips[FRAMES_H][FRAMES_W];

    int frame = 0;
    bool exploded = false;

    void create(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int _x, int _y) ;
    bool destroy(SDL_Rect a, int _x, int _y);
};

#endif // EXPLODE_H
