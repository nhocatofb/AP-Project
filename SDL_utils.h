#ifndef SDL_utils__h
#define SDL_utils__h

#include<SDL.h>
#include<SDL_image.h>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<fstream>

const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 1140;

using namespace std;

void logSDLError(ostream &os, const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void setBackGround(SDL_Renderer *renderer);
bool impact(SDL_Rect a, SDL_Rect b);


#endif // SDL_utils__h
