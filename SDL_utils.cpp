#include "SDL_utils.h"

const string WINDOW_TITLE = "The Virus";
const string WELCOME = "img/welcome.bmp";
const string LOSE = "img/lose.bmp";
const string VICTORY = "img/victory.bmp";

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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) logSDLError(cout, "Mixer", true);
    Mix_Music* music = nullptr;
    music = Mix_LoadMUS("audio/nhacnen.mp3");
    Mix_PlayMusic(music, -1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (TTF_Init() < 0) cout << TTF_GetError() << endl;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
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
    SDL_SetRenderDrawColor(renderer, 199, 248, 226, 255);
    SDL_RenderClear(renderer);
}

bool impact(SDL_Rect _a, SDL_Rect _b) {
    SDL_Rect a = _a;
    SDL_Rect b = _b;
    if(SDL_HasIntersection(&a, &b)==SDL_TRUE) return true;
    return false;
}

void welcome(SDL_Renderer* renderer, int &level) {
    SDL_Rect desRect, sourceRect;
    desRect.x = desRect.y = 0;
    desRect.w = SCREEN_WIDTH;
    desRect.h = SCREEN_HEIGHT;
    SDL_Surface* surface = IMG_Load(WELCOME.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    SDL_Color fg = { 243, 156, 18 };
    TTF_Font* font = TTF_OpenFont("C:/WINDOWS/FONTS/ARIAL.TTF", 20);
    surface = TTF_RenderText_Solid(font, "The Virus", fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    desRect.x = 400; desRect.y = 50;
    desRect.w = 400; desRect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    surface = TTF_RenderText_Solid(font, "<--basic level       advantage level-->", fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    desRect.x = 350; desRect.y = 550;
    desRect.w = 500; desRect.h = 50;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN)) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT: level = 2; break;
            case SDLK_RIGHT: level = 1; break;
            default: break;
            }
            return;
        }
        SDL_Delay(100);
    }
}

void lose(SDL_Renderer* renderer) {
    SDL_Rect desRect, sourceRect;
    desRect.x = desRect.y = 0;
    desRect.w = SCREEN_WIDTH;
    desRect.h = SCREEN_HEIGHT;
    SDL_Surface* surface = IMG_Load(LOSE.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    SDL_Color fg = { 243, 156, 18 };
    TTF_Font* font = TTF_OpenFont("C:/WINDOWS/FONTS/ARIAL.TTF", 20);
    surface = TTF_RenderText_Solid(font, "Press anykey to quit game", fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    desRect.x = 450; desRect.y = 550;
    desRect.w = 300; desRect.h = 50;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
}

void win(SDL_Renderer* renderer) {
    SDL_Rect desRect, sourceRect;
    desRect.x = desRect.y = 0;
    desRect.w = SCREEN_WIDTH;
    desRect.h = SCREEN_HEIGHT;
    SDL_Surface* surface = IMG_Load(VICTORY.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    SDL_Color fg = { 243, 156, 18 };
    TTF_Font* font = TTF_OpenFont("C:/WINDOWS/FONTS/ARIAL.TTF", 20);
    surface = TTF_RenderText_Solid(font, "Press anykey to quit game", fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    desRect.x = 450; desRect.y = 550;
    desRect.w = 300; desRect.h = 50;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
}

