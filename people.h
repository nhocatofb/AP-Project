#ifndef PEOPLE_H
#define PEOPLE_H

#include "SDL_utils.h"
#include "explode.h"

struct People {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture, *infected_texture;
    Explode explode;

    static const int PEOPLE_FRAMES = 4  ;
    const string IMG = "img/people.bmp", IIMG = "img/infected.bmp";
    SDL_Rect clips[PEOPLE_FRAMES];
    int frame = 0;
    int stepX=0, stepY=0;
    float speed = 0;
    bool alive = true;
    string just_move = "none";
    int rdNumber;
    bool infected = false;
    int HP = 1000;


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

#endif // PEOPLE_H
