#include "SDL_utils.h"
#include "player.h"
#include "Bomb.h"
#include "Enemy.h"
#include "wall.h"

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    Player player;
    Enemy enemy1;
    Wall wall(renderer);
    player.loadTexture("img/character.bmp", renderer);
    enemy1.create(renderer);
    while(player.die==false) {
        srand(time(0));
        setBackGround(renderer);
        wall.render(renderer);
        player.bomb.render(renderer);
        player.render(renderer);
        enemy1.render(renderer);
        SDL_Delay(30);
        SDL_RenderPresent(renderer);
        enemy1.move();
        player.event(window, renderer);
        if(impact(player.desRect, enemy1.desRect)==true) player.die=true;
        if(impact(player.desRect, player.bomb.explode_desRect)==true) player.die=true;
    }
    quitSDL(window, renderer);
    return 0;
}

