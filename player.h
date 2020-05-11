#ifndef player_h
#define player_h

#include "SDL_utils.h"
#include "wall.h"
#include "player.h"
#include "bullet.h"

struct Player{
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;

    int stepX=5, stepY=5;
    bool die = false;
    int firstX = SCREEN_HEIGHT/2, firstY = SCREEN_HEIGHT/2;
    int just_move=0, black_list = -1;
    static const int amount_of_walls = 100, amount_of_bullets = 60;
    int number_of_wall_created =0, number_of_bullet_shooted=0;

    static const int FRAMES_W =3, FRAMES_H = 4;
    SDL_Rect clips[FRAMES_H][FRAMES_W];
    int frame =0;

    Wall wall[amount_of_walls];
    Bullet bullet[amount_of_bullets];

    Player(string path, SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer) ;
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBack();
    void event(SDL_Window *window, SDL_Renderer* renderer);
    void shoot(SDL_Renderer *renderer);
    void createWall_top(SDL_Renderer *renderer);
    void createWall_bot(SDL_Renderer *renderer);
    void createWall_left(SDL_Renderer *renderer);
    void createWall_rigth(SDL_Renderer *renderer);
    bool inside();
};


#endif
