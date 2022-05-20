#pragma once

#include <SDL.h>

#include "texture.h"
#include "tiles_map.h"
#include "direction_Vector.h"


const int BULLET_DISPLAY_WIDTH = 10;
const int BULLET_DISPLAY_HEIGHT = 10;
const int BULLET_DAMAGE = 1000;


class BULLET
{
public:
	const int BULLET_MOVE_SPEED = 20;


	BULLET();

	~BULLET();

	void Handle_Bullet(TILE* tiles[]);

	void Render_Bullet_On_Screen(SDL_Renderer* screen, SDL_Rect& camera);

	void Set_start_position(const int& x, const int& y) { Bullet_Rect.x = x; Bullet_Rect.y = y; }

	void Set_Vector_Move_Direction(Direction_Vector in_vector) { move_direction = in_vector; }

	void Set_Is_Bullet_Move(const bool& val) { Is_Bullet_Move = val; }


	SDL_Rect Get_Bullet_Rect() const { return Bullet_Rect; }

	bool Get_Is_Bullet_Move() const { return Is_Bullet_Move; }

private:
	SDL_Rect Bullet_Rect;
	bool Is_Bullet_Move;

	Direction_Vector move_direction;
};

static TEXTURE Bullet_Texture;

bool Load_Bullet_Texture(SDL_Renderer* screen);