#ifndef MAP_H
#define MAP_H

#include "SDL_utils.h"
struct map {
	static const int coefficient = 40, x = 30, y = 16;
	const int tile[y][x] =
	{
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{1,  1,  1,  1,  2,  2,  2,  2,  2,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{3,  1,  1,  1,  1,  1,  1,  5,  1,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{3,  1,  1,  1,  1,  1,  1,  5,  1,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{3,  1,  1,  1,  1,  1,  1,  5,  1,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  2,  4,  4,  4,  4,  2,  4,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  0,  0,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
		{0,  0,  0,  0,  0,  0,  0,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
	   {-0, -0, -0, -0, -0,  0,  3,  1,  1,  2,  2,  2,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
	   {-0,  0, -0,  0, -0,  0,  3,  1,  1,  1,  1,  1,  5,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
	   {-0, -0, -0, -0, -0,  0,  3,  1,  1,  1,  1,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
	   {-0, -0, -0, -0, -0,  0,  0,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9}
	};
	SDL_Texture* park_texture = nullptr,
		* tree_texture = nullptr,
		* ambulance_texture = nullptr,
	    * fire_texture = nullptr;
	SDL_Rect desRect, sourceRect;

	map(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
};





#endif // !MAP_H

#pragma once
