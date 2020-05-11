#ifndef WALL_H
#define WALL_H

#include "SDL_utils.h"
#include "explode.h"

struct Wall {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    Explode explode;
    const string IMG = "img/wall.bmp";
    bool destroy = false;
    static const int frames = 4;
    SDL_Rect clips[frames];
    int frame = 0;

    void create(SDL_Renderer* renderer, int _x, int _y);
    void render(SDL_Renderer *renderer) ;
};


#endif // WALL_H
