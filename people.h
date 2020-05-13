#ifndef PEOPLE_H
#define PEOPLE_H

#include "SDL_utils.h"
#include "explode.h"
#include "map.h"

struct People {
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture = nullptr, * infected_texture = nullptr, * mask_texture= nullptr, *mask2_texture;
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
    int rate = 2;
    string status = "normal";
    int HP = 1000, stress = 500;
    int location[4] = { -1 };


    void create(SDL_Renderer *renderer, int level);
    void render(SDL_Renderer *renderer) ;

    void randomNumber();
    void move(map Map);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    bool inside();
    void moveBack();
    void interact_with_map(map Map);
};

#endif // PEOPLE_H
