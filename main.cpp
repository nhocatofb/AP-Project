#include "SDL_utils.h"

struct Player{
    SDL_Rect sourceRect;
    SDL_Rect desRect;
    SDL_Texture* texture;

    void loadTexture(string path, SDL_Renderer *renderer) {
        SDL_Surface* surface = SDL_LoadBMP(path.c_str());
        //SDL_FreeSurface(surface);
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
        sourceRect.x = desRect.x = 0;
        sourceRect.y = desRect.y = 0;
        desRect.w = sourceRect.w;
        desRect.h = sourceRect.h;
    }

    void render(SDL_Renderer *renderer) {
        SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    }

    void moveRight() {
        desRect.x +=50;
    }
    void moveLeft() {
        desRect.x -=50;
    }
    void moveUp() {
        desRect.y -=50;
    }
    void moveDown() {
        desRect.y +=50;
    }
};

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Player player;
    player.loadTexture("img/character.bmp", renderer);
    SDL_Event e;
    while(true) {
    setBackGround(renderer);
    player.render(renderer);
	SDL_RenderPresent(renderer);
	//SDL_Delay(100);
	if(SDL_PollEvent(&e)==0) continue;
        if(e.type == SDL_QUIT) break;
        if(e.type==SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT: player.moveLeft(); break;
            case SDLK_RIGHT: player.moveRight(); break;
            case SDLK_UP: player.moveUp(); break;
            case SDLK_DOWN: player.moveDown(); break;
            default: break;
            }
        }
    }


    quitSDL(window, renderer);
    return 0;
}

