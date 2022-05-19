#pragma once

#include "tiles_map.h"

bool check_collision(SDL_Rect A, SDL_Rect B);

bool touch_wall(SDL_Rect object, TILE* tiles[]);