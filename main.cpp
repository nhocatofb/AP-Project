#include<iostream>
#include<SDL.h>
#include "SDL_utils.h"

const int SCREEN_HEIGHT = 500;
const int SCREEN_WIDTH = 500;

struct Box {
    int x;
    int y;
    int size = 10;
    int stepX =5;
    int stepY = 5;

    void render(SDL_Renderer* renderer) {
        SDL_Rect square;
        square.x = x;
        square.y = y;
        square.w = size;
        square.h = size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &square);
    }

    void move() {
        x+= stepX;
        y+= stepY;
    }
    void moveLeft() {
        stepX = -5;
        stepY = 0;
    }
    void moveRight() {
        stepX= 5;
        stepY= 0;
    }
    void moveUp() {
        stepY = -5;
        stepX = 0;
    }
    void moveDown() {
        stepY = 5;
        stepX = 0;
    }

    bool inside(int minX, int minY, int maxX, int maxY) {
        return (x>=minX && y>=minY && x+size<=maxX && y+size<=maxY);
    }
};

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //Ve o day
    Box box;
    box.x = 0;
    box.y = 0;
    SDL_Event e;
    while(box.inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        box.render(renderer);
        SDL_RenderPresent(renderer);
        box.move();
        SDL_Delay(100);
        if(SDL_PollEvent(&e)==0) continue;
        if(e.type == SDL_QUIT) break;
        if(e.type==SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT: box.moveLeft(); break;
            case SDLK_RIGHT: box.moveRight(); break;
            case SDLK_UP: box.moveUp(); break;
            case SDLK_DOWN: box.moveDown(); break;
            default: break;
            }
        }
    }
    //ket thuc

    waitUntilKeyPressed();
    quitSDL(window, renderer);

    return 0;
}

