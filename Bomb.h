#ifndef BOMB_H
#define BOMB_H

#include "SDL_utils.h"

struct Bomb {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    static const int BOMB_FRAMES = 4;
    const string IMG = "img/bomb.bmp";
    SDL_Rect clips[BOMB_FRAMES];
    int frame = 0;

    void create(SDL_Renderer *renderer, int _x, int _y);
    void render(SDL_Renderer *renderer) ;

};




#endif // BOMB_H
