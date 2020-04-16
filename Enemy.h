#ifndef ENEMY_H
#define ENEMY_H

#include "SDL_utils.h"

struct Enemy {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    int stepX=0;
    int stepY=0;

    void create(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer) ;

    string canMove();
    void move();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    bool inside(int minX, int minY, int maxX, int maxY);
};




#endif // ENEMY_H
