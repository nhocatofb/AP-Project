#include "SDL_utils.h"
#include "player.h"
#include "Bomb.h"
#include "Enemy.h"

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Player player;
    Enemy enemy;
    player.loadTexture("img/character.bmp", renderer);
    enemy.create(renderer);
    while(player.inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        setBackGround(renderer);
        player.bomb.render(renderer);
        player.render(renderer);
        enemy.render(renderer);
        SDL_Delay(30);
        SDL_RenderPresent(renderer);
        enemy.move();
        player.event(window, renderer);
    }
    quitSDL(window, renderer);
    return 0;
}

