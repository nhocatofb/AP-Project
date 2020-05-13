#ifndef BULLET_H
#define BULLET_H

#include "SDL_utils.h"
#include "explode.h"

struct Bullet {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    Explode explode;

    int stepX=7, stepY=0;
    const string IMG = "img/bomb.bmp";
    bool destroy = false;
    string just_move;
    int speed = 1;
    static const int frames = 2;
    int frame = 0;
    SDL_Rect clips[frames];

    void create(SDL_Renderer* renderer, int _x, int _y);
    void render(SDL_Renderer *renderer) ;
    void move();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    bool inside();
};



#endif // BULLET_H
