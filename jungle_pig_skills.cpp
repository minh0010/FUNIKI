#include "jungle_pig_skills.h"
#include "function.h"

// boss bullet

BOSS_BULLET::BOSS_BULLET()
{
	boss_bullet_rect = { 0,0,BOSS_BULLET_DISPLAY_WIDTH,BOSS_BULLET_DISPLAY_HEIGHT };
	is_bullet_move = false;
	BOSS_BULLET_MOVE_SPEED = 0;
	move_direction = Direction_Vector(0.0, 0.0);
}

BOSS_BULLET::~BOSS_BULLET()
{

}

void BOSS_BULLET::Handle_BOSS_BULLET(TILE* tiles[])
{
	boss_bullet_rect.x += (int)(BOSS_BULLET_MOVE_SPEED * move_direction.a);
	boss_bullet_rect.y += (int)(BOSS_BULLET_MOVE_SPEED * move_direction.b);

	if (touch_wall(boss_bullet_rect, tiles))
	{
		is_bullet_move = false;
	}
}

void BOSS_BULLET::Render_BOSS_BULLET_On_Screen(SDL_Renderer* screen, SDL_Rect& camera)
{
	if (is_bullet_move)
	{
		if (check_collision(boss_bullet_rect, camera))
		{
			boss_bullet_texture.render_texture_on_screen(boss_bullet_rect.x - camera.x, boss_bullet_rect.y - camera.y, screen);
		}
	}
}

bool Load_Jungle_Pig_Bullet_Texture(SDL_Renderer* screen)
{
	bool load = boss_bullet_texture.load_texture_from_file("GAME_TEXTURE/BULLET/red-circle.png", screen, true, 255, 255, 255);
	if (load)
	{
		boss_bullet_texture.Set_Display_Width(BOSS_BULLET_DISPLAY_WIDTH);
		boss_bullet_texture.Set_Display_Height(BOSS_BULLET_DISPLAY_HEIGHT);
	}
	return load;
}





// boss meteo

METEO::METEO()
{
	METEO_POS = { 0,0,METEO_WIDTH, METEO_HEIGHT };
	Is_Boss_Meteo_Falling = false;
	Is_Create_Lava_Pool = false;
	Limit = 0;

	is_get_time = false;
	rotTime = 0;
	LAVA_POS = { 0,0,0,0 };
	red_x_pos = { 0,0,0,0 };

	frame = 0;

	lava_center_x = 0;
	lava_center_y = 0;

	delay_damage_time = 0;
}

METEO::~METEO()
{
}

void METEO::delay_lava_pool()
{
	if (is_get_time && (SDL_GetTicks() - rotTime > 3000))
	{
		Is_Create_Lava_Pool = false;
	}
}

void METEO::handle_meteo()
{
	METEO_POS.y += METEO_SPEED;
	if (METEO_POS.y + METEO_HEIGHT > Limit && Is_Boss_Meteo_Falling)
	{
		Is_Boss_Meteo_Falling = false;
		Is_Create_Lava_Pool = true;
		is_get_time = true;
		delay_damage_time = SDL_GetTicks();
		rotTime = SDL_GetTicks();
	}
}

void METEO::render_meteo(SDL_Renderer* screen, SDL_Rect& camera)
{
	if (Is_Boss_Meteo_Falling && !Is_Create_Lava_Pool)
	{
		Meteo_Texture.render_texture_on_screen(METEO_POS.x - camera.x, METEO_POS.y - camera.y, screen, &Meteo_frame[frame]);
		frame++;
		if (frame >= METEO_total_frame) frame = 0;
	}
	else Lava_Texuture.render_texture_on_screen(LAVA_POS.x - camera.x, LAVA_POS.y - camera.y, screen);
}

void METEO::render_meteo_falling_position(SDL_Renderer* screen, SDL_Rect& camera)
{
	red_x_texture.render_texture_on_screen(red_x_pos.x - camera.x, red_x_pos.y - camera.y, screen);
}

bool METEO::delay_damage()
{
	if (Is_Create_Lava_Pool)
	{
		if (SDL_GetTicks() - delay_damage_time >= 1000)
		{
			delay_damage_time = SDL_GetTicks();
			return false;
		}
	}


	return true;
}


bool load_jungle_pig_skill_texture(SDL_Renderer* screen)
{
	// load meteo texture
	if (!Meteo_Texture.load_texture_from_file("GAME_TEXTURE/BULLET/meteo.png", screen, true, 255, 255, 255))
	{
		return false;
	}
	else
	{
		Meteo_Texture.Set_Display_Height(METEO_HEIGHT);
		Meteo_Texture.Set_Display_Width(METEO_WIDTH);

		Meteo_frame[0] = { 670,30,120,250 };
		Meteo_frame[1] = { 670,260,120,250 };
		Meteo_frame[2] = { 674,490,120,250 };
		Meteo_frame[3] = { 674,720,120,250 };
		Meteo_frame[4] = { 535,30,120,250 };
		Meteo_frame[5] = { 535,260,120,250 };
		Meteo_frame[6] = { 535,490,120,250 };
		Meteo_frame[7] = { 535,720,120,250 };
		Meteo_frame[8] = { 395,30,120,250 };
		Meteo_frame[9] = { 395,260,120,250 };
		Meteo_frame[10] = { 395,490,120,250 };
		Meteo_frame[11] = { 395,720,120,250 };
		Meteo_frame[12] = { 258,30,120,250 };
		Meteo_frame[13] = { 258,260,120,250 };
		Meteo_frame[14] = { 258,490,120,250 };
		Meteo_frame[15] = { 258,720,120,250 };
		Meteo_frame[16] = { 125,260,120,250 };
		Meteo_frame[17] = { 125,490,120,250 };
	}



	// load lava texture
	if (!Lava_Texuture.load_texture_from_file("GAME_TEXTURE/BULLET/red-circle.png", screen, true, 255, 255, 255))
	{
		return false;
	}
	else
	{
		Lava_Texuture.setBlend_mode(SDL_BLENDMODE_BLEND);
		Lava_Texuture.setAlpha(150);

		Lava_Texuture.Set_Display_Height(LAVA_SIZE);
		Lava_Texuture.Set_Display_Width(LAVA_SIZE);
	}


	// load red x texture 
	if (!red_x_texture.load_texture_from_file("GAME_TEXTURE/BULLET/red_x.png", screen, true, 255, 255, 255))
	{
		return false;
	}
	else
	{
		red_x_texture.Set_Display_Height(RED_X_SIZE);
		red_x_texture.Set_Display_Width(RED_X_SIZE);
	}
	return true;
}