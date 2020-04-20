#include "SDL_utils.h"

const string WINDOW_TITLE = "Demo SDL by LoAnhDuc";

void logSDLError(ostream &os, const string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << endl;
    if(fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
        logSDLError(cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr) logSDLError(cout, "Create Window", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) logSDLError(cout, "Create Renderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
        return;
        SDL_Delay(100);
    }
}

void setBackGround(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
}

bool impact(SDL_Rect a, SDL_Rect b) {
    if((a.x+a.w >= b.x && a.x+a.w <= b.x+b.w) && (a.y+a.h >= b.y && a.y+a.h <= b.y+b.h)) return true;
    if((a.x >= b.x && a.x <= b.x+b.w) && (a.y+a.h >= b.y && a.y+a.h <= b.y+b.h)) return true;
    if((a.x+a.w >= b.x && a.x+a.w <= b.x+b.w) && (a.y >= b.y && a.y <= b.y+b.h)) return true;
    if((a.x >= b.x && a.x <= b.x+b.w) && (a.y >= b.y && a.y <= b.y+b.h)) return true;
    return false;
}


