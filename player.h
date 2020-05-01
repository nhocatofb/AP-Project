#ifndef player_h
#define player_h

#include "SDL_utils.h"
#include "Bomb.h"
#include "wall.h"

struct Player{
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;

    int stepX=5, stepY=5;
    bool die = false;
    int firstX = 40, firstY =40;
    string just_move;
    static const int amount_of_walls = 100;
    int number_of_wall_created =0;

    Bomb bomb;
    Wall wall[amount_of_walls];

    Player(string path, SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer) ;
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBack();
    void event(SDL_Window *window, SDL_Renderer* renderer);
    void createBomb(SDL_Renderer *renderer);
    void createWall_top(SDL_Renderer *renderer);
    void createWall_bot(SDL_Renderer *renderer);
    void createWall_left(SDL_Renderer *renderer);
    void createWall_rigth(SDL_Renderer *renderer);
};


#endif
