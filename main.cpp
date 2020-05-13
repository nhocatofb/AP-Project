#include "SDL_utils.h"
#include "player.h"
#include "Enemy.h"
#include "people.h"
#include "explode.h"
#include "map.h"

const int amout_of_enemys = 100;
const int amout_of_people = 50;

void renderScore(SDL_Renderer* renderer, int score);

int main(int argc, char* argv[]) {
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    int score = 0;
    int level = -1;
    welcome(renderer, level);

    map Map(renderer);
    Player player("img/character.bmp", renderer);
    Enemy enemy[amout_of_enemys];
    for (int i = 0; i < amout_of_enemys; i++) {
        enemy[i].create(renderer);
    }
    int count_enemy =0;

    People people[amout_of_people];
    for (int i = 0; i < amout_of_people; i++) {
        people[i].create(renderer, level);
    }

    while(player.die==false) {
        int countEnemy = amout_of_enemys, countPeople = amout_of_people;

        setBackGround(renderer);
        renderScore(renderer, score);
        Map.render(renderer);
        player.render(renderer);

        for(int i=0; i<player.number_of_bullet_shooted; i++) {
            player.bullet[i].render(renderer);
            if(impact(player.desRect, player.bullet[i].desRect)==true) player.die = true;
        }
        for (int i = 0; i < amout_of_people; i++) {
            if (people[i].desRect.w != 0) break;
            if (i == amout_of_people - 1) player.die = true;
        }

    //Xu ly buc tuong
        for(int i=0; i<player.number_of_wall_created; i++) {
            player.wall[i].render(renderer);
            if (impact(player.desRect, player.wall[i].desRect) == true) player.moveBack();
        }
    //xu ly nguoi dan
        for(int i=0; i<amout_of_people; i++) {
            people[i].render(renderer);
            people[i].move(Map);
            for (int j = 0; j<player.number_of_bullet_shooted; j++) {
                if (impact(people[i].desRect, player.bullet[j].desRect) == true) {
                    people[i].rdNumber=50;
                    if (rand() % 4 == 0) people[i].infected = false;
                    player.bullet[j].destroy = true;
                }
            }
            for(int j=i+1; j<amout_of_people; j++) {                 
                if (impact(people[i].desRect, people[j].desRect) == true && (people[i].infected==true|| people[j].infected==true) && rand()%people[i].rate==1)
                    people[i].infected = people[j].infected = true;
            }
            for(int j=0; j<player.number_of_wall_created; j++) {
                if (impact(people[i].desRect, player.wall[j].desRect) == true) {
                    people[i].moveBack();
                    if(rand()%20==0) player.wall[j].frame++;
                }
            }
            if (people[i].alive == false) countPeople--;
        }
    //xu ly ke dich
        if(count_enemy<amout_of_enemys*level*150) count_enemy++;
        for(int i=0; i<count_enemy/(level*150); i++) {
            enemy[i].render(renderer);
            enemy[i].move();
            for(int j=0; j<count_enemy/200; j++) {
                if (enemy[i].explode.destroy(enemy[j].desRect, enemy[i].desRect.x, enemy[i].desRect.y) == true) {
                    enemy[j].alive = false;
                    score++;
                }
            }
            for(int j=0; j<amout_of_people; j++) {
                if (enemy[i].explode.destroy(people[j].desRect, enemy[i].desRect.x, enemy[i].desRect.y) == true)
                    people[j].alive = false;
                if (people[j].explode.destroy(enemy[i].desRect, people[j].desRect.x, people[j].desRect.y) == true) {
                    enemy[i].alive = false;
                    score++;
                }
            }
            if(impact(player.desRect, enemy[i].desRect)==true) player.die = true;
            for(int j=0; j<player.number_of_wall_created; j++) {
                if (impact(enemy[i].desRect, player.wall[j].desRect) == true) {
                    enemy[i].moveBack();
                    player.wall[j].frame++;
                }
            }
            for(int j=0; j<amout_of_people; j++) {
                int x = rand() % 2;
                if (impact(enemy[i].desRect, people[j].desRect) == true && x == 1) {
                    people[j].infected = true;
                }
            }
            for(int j=0; j<player.number_of_bullet_shooted; j++) {
                if(impact(enemy[i].desRect, player.bullet[j].desRect)==true) {
                    enemy[i].alive = false;
                    player.bullet[j].destroy = true;
                    score++;
                }
            }
            if (enemy[i].alive == false) countEnemy--;
        }
        SDL_Delay(30);
        SDL_RenderPresent(renderer);
        player.event(window, renderer);
        if (countPeople == 0) player.die = true;
        if (countEnemy == 0) break;
        if (player.amount_of_bullets < player.number_of_bullet_shooted) player.die = true;
    }
    if (player.die == true) lose(renderer);
    else win(renderer);
    quitSDL(window, renderer);
    return 0;
}

void renderScore(SDL_Renderer* renderer, int score) {
    SDL_Color fg = { 243, 156, 18 };
    TTF_Font* font = TTF_OpenFont("C:/WINDOWS/FONTS/ARIAL.TTF", 20);
    SDL_Rect desRect;
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    stringstream ss;
    ss << score;
    string str = "Your score: ";
    str += ss.str();

    surface =  TTF_RenderText_Solid(font,str.c_str(), fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    desRect.x = 800; desRect.y = 0;
    desRect.w = 80; desRect.h = 20;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);
    SDL_DestroyTexture(texture);
}

