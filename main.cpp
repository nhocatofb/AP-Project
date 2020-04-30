#include "SDL_utils.h"
#include "player.h"
#include "Bomb.h"
#include "Enemy.h"

const int amout_of_enemys = 100;

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Player player("img/character.bmp", renderer);
    Enemy enemy[amout_of_enemys](renderer);
    int count_enemy =0;

    while(player.die==false) {
        srand(time(0));
        if(count_enemy<1000) count_enemy++;

        setBackGround(renderer);
        for(int i=0; i<10; i++) {
            enemy[i].render(renderer);
            enemy[i].move();
            if(impact(player.desRect, enemy[i].desRect)==true) player.die = true;
            if(impact(player.bomb.desRect, enemy[i].desRect)==true) ;
        }
        for(int i=0; i<player.number_of_wall_created; i++) {
            player.wall[i].render(renderer);
            if(impact(player.desRect, player.wall[i].desRect)==true) player.moveBack();
        }
        player.bomb.render(renderer);
        player.render(renderer);

        SDL_Delay(30);
        SDL_RenderPresent(renderer);

        player.event(window, renderer);
    }
    quitSDL(window, renderer);
    return 0;
}

