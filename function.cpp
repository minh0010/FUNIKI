#include "function.h"

bool check_collision(SDL_Rect A, SDL_Rect B)
{
	int topA = A.y, bottomA = A.y + A.h, leftA = A.x, rightA = A.x + A.w;
	int topB = B.y, bottomB = B.y + B.h, leftB = B.x, rightB = B.x + B.w;
	if (topA >= bottomB) return false;
	if (bottomA <= topB) return false;
	if (leftA >= rightB) return false;
	if (rightA <= leftB) return false;

	return true;
}

bool touch_wall(SDL_Rect object, TILE* tiles[])
{
	for (int i = 0; i < TOTAL_TILE_LEVEL_1; ++i)
	{
		if (tiles[i]->get_tile_type() == WALL_TOP_PATH)
		{
			if (check_collision(object, tiles[i]->get_mPath()))
			{
				return true;
			}
		}
	}
	return false;
}