#ifndef BOMB_H
#define BOMB_H

#include "SDL_utils.h"
#include "Enemy.h"
#include "wall.h"

struct Player;

struct Bomb {
    SDL_Rect sourceRect, explode_sourceRect;
    SDL_Rect desRect, explode_desRect;
    SDL_Texture* texture , *explode_texture;

    const string BombIMG = "img/bomb.bmp", ExplodeIMG = "img/explode.bmp";

    static const int BOMB_FRAMES = 4, EXPLODE_FRAMES_H = 7, EXPLODE_FRAMES_W = 4;
    SDL_Rect clips[BOMB_FRAMES], explode_clips[EXPLODE_FRAMES_H][EXPLODE_FRAMES_W];

    int frame = 0;
    int timeToExplode = 40;
    bool isCreate = false;

    void create(SDL_Renderer *renderer, int _x, int _y);
    void render(SDL_Renderer *renderer) ;
    void explode(SDL_Renderer *renderer);
    void destroy(Player *player, Enemy enemy, Wall wall);
};




#endif // BOMB_H
