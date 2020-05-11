#include "player.h"

Player::Player(string path, SDL_Renderer *renderer) {
        SDL_Surface* surface = SDL_LoadBMP(path.c_str());
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);

        for(int i=0; i<FRAMES_H; i++) {
            for(int j=0; j<FRAMES_W; j++) {
                clips[i][j].x = sourceRect.w*j/FRAMES_W;
                clips[i][j].y = sourceRect.h*i/FRAMES_H;
                clips[i][j].w = sourceRect.w/FRAMES_W;
                clips[i][j].h = sourceRect.h/FRAMES_H;
            }
        }

        desRect.x = firstX;
        desRect.y = firstY;
}

void Player::render(SDL_Renderer *renderer) {
    if(frame == FRAMES_W) frame =0;
    sourceRect.x = clips[just_move][frame].x;
    sourceRect.y = clips[just_move][frame].y;
    sourceRect.h = clips[just_move][frame].h;
    sourceRect.w = clips[just_move][frame].w;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
    if(inside()==false) moveBack();
    if(frame==0) black_list = -1;
}

void Player::moveRight() {
    if(black_list!=0) {
        just_move = 0;
        desRect.x +=stepX;
    }
    frame++;
}
void Player::moveLeft() {
    if(black_list!=1) {
        just_move = 1;
        desRect.x -=stepX;
    }
    frame++;
}
void Player::moveUp() {
    if(black_list!=2) {
        just_move = 2;
        desRect.y -=stepY;
    }
    frame++;
}
void Player::moveDown() {
    if(black_list!=3) {
        just_move = 3;
        desRect.y +=stepY;
    }
    frame++;
}

void Player::moveBack() {
    if(just_move==0) {
        moveLeft();
        black_list = 0;
    }
    else if(just_move==1) {
        moveRight();
        black_list = 1;
    }
    else if(just_move==2) {
        moveDown();
        black_list = 2;
    }
    else if(just_move==3)  {
        moveUp();
        black_list = 3;
    }
}

void Player::shoot(SDL_Renderer* renderer) {
    if(number_of_bullet_shooted<amount_of_bullets) {
        if(just_move==0) {
            bullet[number_of_bullet_shooted].create(renderer, desRect.x+desRect.w+1, desRect.y);
            bullet[number_of_bullet_shooted].moveRight();
        }
        else if(just_move==1) {
            bullet[number_of_bullet_shooted].create(renderer, desRect.x-20, desRect.y);
            bullet[number_of_bullet_shooted].moveLeft();
        }
        else if(just_move==2) {
            bullet[number_of_bullet_shooted].create(renderer, desRect.x, desRect.y-20);
            bullet[number_of_bullet_shooted].moveUp();
        }
        else if(just_move==3) {
            bullet[number_of_bullet_shooted].create(renderer, desRect.x, desRect.y+desRect.h+1);
            bullet[number_of_bullet_shooted].moveDown();
        }
        number_of_bullet_shooted++;
    }
}

void Player::createWall_top(SDL_Renderer *renderer) {
    if(number_of_wall_created<amount_of_walls) {
        wall[number_of_wall_created].create(renderer, desRect.x, desRect.y-wall[0].desRect.h-1);
        number_of_wall_created++;
    }
}

void Player::createWall_bot(SDL_Renderer *renderer) {
    if(number_of_wall_created<amount_of_walls) {
        wall[number_of_wall_created].create(renderer, desRect.x, desRect.y+desRect.h+1);
        number_of_wall_created++;
    }
}

void Player::createWall_left(SDL_Renderer *renderer) {
    if(number_of_wall_created<amount_of_walls) {
        wall[number_of_wall_created].create(renderer, desRect.x-wall[0].desRect.w-1, desRect.y);
        number_of_wall_created++;
    }
}

void Player::createWall_rigth(SDL_Renderer *renderer) {
    if(number_of_wall_created<amount_of_walls) {
        wall[number_of_wall_created].create(renderer, desRect.x+desRect.w+1, desRect.y);
        number_of_wall_created++;
    }
}

void Player::event(SDL_Window *window, SDL_Renderer* renderer){
    SDL_Event e;
    if(SDL_PollEvent(&e)==0) {};
    if(e.type == SDL_QUIT) quitSDL(window, renderer);
    if(e.type==SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE: break;
        case SDLK_LEFT: moveLeft(); break;
        case SDLK_RIGHT: moveRight(); break;
        case SDLK_UP: moveUp(); break;
        case SDLK_DOWN: moveDown(); break;
        case SDLK_SPACE: shoot(renderer); break;
        case SDLK_w: createWall_top(renderer); break;
        case SDLK_a: createWall_left(renderer); break;
        case SDLK_d: createWall_rigth(renderer); break;
        case SDLK_s: createWall_bot(renderer); break;
        default: break;
        }
    }
}

bool Player::inside() {
    return (desRect.x>=0 && desRect.y>=0 && desRect.x+desRect.w<= SCREEN_WIDTH && desRect.y+desRect.h<=SCREEN_HEIGHT);
}
