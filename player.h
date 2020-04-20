#ifndef player_h
#define player_h

#include "SDL_utils.h"
#include "Bomb.h"

struct Player{
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;
    Bomb bomb;
    int stepX=5;
    int stepY=5;
    bool die = false;

    void loadTexture(string path, SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer) ;

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    bool inside(int minX, int minY, int maxX, int maxY);
    void event(SDL_Window *window, SDL_Renderer* renderer);
    void createBomb(SDL_Renderer *renderer);
};

#endif
