#include<SDL.h>
#include<iostream>

using namespace std;

void logSDLError(ostream &os, const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
