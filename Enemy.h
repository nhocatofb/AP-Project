#ifndef ENEMY_H
#define ENEMY_H

#include "SDL_utils.h"
#include "explode.h"

struct Enemy {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    Explode explode;

    static const int ENEMY_FRAMES = 2;
    const string IMG = "img/enemy.bmp";
    SDL_Rect clips[ENEMY_FRAMES];
    int frame = 0;
    int stepX = 0, stepY = 0;
    float speed = 0;
    bool alive = true;
    string just_move = "none";
    int rdNumber;

    void create(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer) ;

    void randomNumber();
    void move();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    bool inside();
    void moveBack();
};




#endif // ENEMY_H
