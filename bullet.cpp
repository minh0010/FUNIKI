#include <iostream>

#include "Bullet.h"
#include "function.h"


BULLET::BULLET()
{
	Bullet_Rect = { 0,0,BULLET_DISPLAY_WIDTH,BULLET_DISPLAY_HEIGHT };
	Is_Bullet_Move = false;
	move_direction = Direction_Vector(0.0, 0.0);
}

BULLET::~BULLET()
{

}

void BULLET::Handle_Bullet(TILE* tiles[])
{
	Bullet_Rect.x += (int)(BULLET_MOVE_SPEED * move_direction.a);
	Bullet_Rect.y += (int)(BULLET_MOVE_SPEED * move_direction.b);

	if (touch_wall(Bullet_Rect, tiles))
	{

		Is_Bullet_Move = false;
	}
}

void BULLET::Render_Bullet_On_Screen(SDL_Renderer* screen, SDL_Rect& camera)
{
	if (Is_Bullet_Move)
	{
		if (check_collision(Bullet_Rect, camera))
		{
			Bullet_Texture.render_texture_on_screen(Bullet_Rect.x - camera.x, Bullet_Rect.y - camera.y, screen);
		}
	}
}


bool Load_Bullet_Texture(SDL_Renderer* screen)
{
	bool load = Bullet_Texture.load_texture_from_file("GAME_TEXTURE/BULLET/red-circle.png", screen, true, 255, 255, 255);
	if (!load)
	{
		cout << "fail to load bullet texture\n";
		return load;
	}
	else
	{
		Bullet_Texture.Set_Display_Width(BULLET_DISPLAY_WIDTH);
		Bullet_Texture.Set_Display_Height(BULLET_DISPLAY_HEIGHT);
	}
	return load;
}