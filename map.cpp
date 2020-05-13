#include "map.h"
map::map(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("img/park.bmp");
    park_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("img/tree.bmp");
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    tree_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("img/ambulance.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    ambulance_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("img/fire.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    fire_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    sourceRect.x = 0;
    sourceRect.y = 0;
}
void map::render(SDL_Renderer* renderer) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (tile[i][j] == 1) {
                desRect.x = j * coefficient;
                desRect.y = i * coefficient;
                SDL_QueryTexture(park_texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
                desRect.w = sourceRect.w;
                desRect.h = sourceRect.h;
                SDL_RenderCopy(renderer, park_texture, &sourceRect, &desRect);
            }
            if (tile[i][j] == 2 || tile[i][j] == 3 || tile[i][j] == 5) {
                desRect.x = j * coefficient;
                desRect.y = i * coefficient;
                SDL_QueryTexture(tree_texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
                desRect.w = sourceRect.w;
                desRect.h = sourceRect.h;
                SDL_RenderCopy(renderer, tree_texture, &sourceRect, &desRect);
            }
            if (tile[i][j] == 6) {
                desRect.x = j * coefficient;
                desRect.y = i * coefficient;
                SDL_QueryTexture(ambulance_texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
                desRect.w = sourceRect.w;
                desRect.h = sourceRect.h;
                SDL_RenderCopy(renderer, ambulance_texture, &sourceRect, &desRect);
            }
            if (tile[i][j] == 9) {
                desRect.x = j * coefficient;
                desRect.y = i * coefficient;
                SDL_QueryTexture(fire_texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
                desRect.w = sourceRect.w;
                desRect.h = sourceRect.h;
                SDL_RenderCopy(renderer, fire_texture, &sourceRect, &desRect);
            }
        }
    }
}
