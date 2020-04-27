#ifndef WALL_H
#define WALL_H

#include "SDL_utils.h"

struct Wall {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    //static const int ENEMY_FRAMES = 2;
    const string IMG = "img/wall.bmp";
    //SDL_Rect clips[ENEMY_FRAMES];
    //int frame = 0;
    Wall(SDL_Renderer* renderer);
    void render(SDL_Renderer *renderer) ;
};





#endif // WALL_H
