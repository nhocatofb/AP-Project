#include "people.h"

void People::create(SDL_Renderer *renderer, int level) {
    SDL_Surface* surface = SDL_LoadBMP(IMG.c_str());
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP(IIMG.c_str());
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    infected_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("img/mask.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    mask_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("img/mask2.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    mask2_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
    desRect.x = rand()%(SCREEN_WIDTH*2/3);
    desRect.y = rand()%(SCREEN_HEIGHT-sourceRect.h) +1;
    for(int i=0; i<PEOPLE_FRAMES; i++) {
        clips[i].x = sourceRect.w*i/PEOPLE_FRAMES;
        clips[i].y = 0;
        clips[i].w = sourceRect.w/PEOPLE_FRAMES;
        clips[i].h = sourceRect.h;
    }
    explode.create(renderer);
}

void People::render(SDL_Renderer *renderer) {
    if(alive==false || HP<=0) {
        desRect.w =0;
        desRect.h =0;
        explode.render(renderer, desRect.x, desRect.y);
        return;
    }
    sourceRect.x = clips[frame/20].x;
    sourceRect.y = clips[frame/20].y;
    sourceRect.h = clips[frame/20].h;
    sourceRect.w = clips[frame/20].w;
    desRect.w = sourceRect.w*4/5;
    desRect.h = sourceRect.h*4/5;
    frame++;
    if(frame/20==PEOPLE_FRAMES) frame =0;
    if(infected==true) {
        HP--;
        if(HP<=500) {
            SDL_RenderCopy(renderer, infected_texture, &sourceRect, &desRect);
            return;
        }
    }
    if (status == "mask") {
        SDL_RenderCopy(renderer, mask_texture, &sourceRect, &desRect);
        return;
    }
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    HP++;
    if (HP > 1000) HP = 1000;
}

void People::randomNumber() {
    if(rdNumber<20) rdNumber = rand() % 20 + 1;
    else if(rdNumber>20 && rdNumber<40) rdNumber = rand()%20+20 +1;
    else if(rdNumber>40 && rdNumber<60) rdNumber = rand()%20+40 +1;
    else if(rdNumber>60 && rdNumber<80) rdNumber = rand()%20+60 +1;
    else rdNumber = rand() % 80 + 1;
}

void People::move(map Map) {
    if (alive == false || HP <= 0) { alive = false; return; }
    randomNumber();
    interact_with_map(Map);
    if(rdNumber%5==0) speed =1.5;
    else if(rdNumber%5==1) speed = 0.5;
    else speed = 1;

    if(rdNumber <= 20 && inside()==true) moveRight();
    else if (rdNumber <= 40 && inside()==true) moveUp();
    else if (rdNumber <= 60 && inside()==true) moveLeft();
    else if (rdNumber <= 80 && inside()==true) moveDown();
    if (inside() == false) moveBack();
    desRect.x += stepX;
    desRect.y += stepY;
}

void People::moveRight() {
        stepX=2*speed;
        stepY=0;
        just_move = "right";
}
void People::moveLeft() {
        stepX= -2*speed;
        stepY=0;
        just_move = "left";
}
void People::moveUp() {
        stepX=0;
        stepY=-2*speed;
        just_move = "up";
}
void People::moveDown() {
        stepX=0;
        stepY=2*speed;
        just_move = "down";
}

void People::moveBack() {
    if(just_move=="right") moveLeft();
    else if(just_move=="left") moveRight();
    else if(just_move=="up") moveDown();
    else if(just_move=="down") moveUp();
    desRect.x += stepX;
    desRect.y += stepY;
    rdNumber = rand() % 80 + 1;
}

bool People::inside() {
    return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
}

void People::interact_with_map(map Map) {
    int left_x = desRect.x / Map.coefficient,
        right_x = (desRect.x + desRect.w) / Map.coefficient;
    int bot_y = desRect.y / Map.coefficient,
        top_y = (desRect.y + desRect.h) / Map.coefficient;
    int temp = 0;
    for (int i = bot_y; i <= top_y; i++) {
        for (int j = left_x; j <= right_x; j++) {
            location[temp] = Map.tile[i][j];
            temp++;
        }
    }
    if (location[0] == 0 && location[1] == 0 && location[2] == 0 && location[3] == 0) return;
    for (int i = 0; i < 4; i++) {
        if (location[i] == 2) rdNumber = 70;
        else if (location[i] == 3) rdNumber = 10;
        else if (location[i] == 4) rdNumber = 30;
        else if (location[i] == 5) rdNumber = 50;
        if (location[i] == 9) alive = false;
        if (location[i] == 6 && infected == false && rand()%5==0) {
            status = "mask";
            rate = 4;
        }
    }
}
