#ifndef BOMB_H
#define BOMB_H

#include "SDL_utils.h"

struct Bomb {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;

    void create(SDL_Renderer *renderer, int _x, int _y);
    void render(SDL_Renderer *renderer) ;

};




#endif // BOMB_H
