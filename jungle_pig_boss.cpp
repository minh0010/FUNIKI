#include <iostream>
#include <math.h>

#include "jungle_pig_boss.h"
#include "function.h"

JUNGLEPIG::JUNGLEPIG()
{
	Jungle_Pig_Rect = { 0,0,JUNGLE_PIG_WIDTH, JUNGLE_PIG_HEIGHT };
	Jungle_Pig_Collision_Box = { 0,0,145,90 };
	frame = 0;
	boss_look_direction = SDL_FLIP_HORIZONTAL;

	new_position_x = 0; new_position_y = 0;
	is_jungle_pig_move = false;

	jungle_pig_skill = 0;
	skills_rotTime = 0;
	move_rotTime = 0;
	fire_toward_to_player_rotTime;

	BOSS_MODE = EASY;

	it_time_to_fight = false;
	Is_Jungle_Pig_Alive = true;
}

JUNGLEPIG::~JUNGLEPIG()
{
	TEXTURE::free();
}

bool JUNGLEPIG::Load_Jungle_Pig_Texture(SDL_Renderer* screen)
{
	if (!TEXTURE::load_texture_from_file("GAME_TEXTURE/JUNGLE_PIG_TEXTURE/jungle_pig.png", screen, true, 0, 125, 180))
	{
		cout << "some fail with jungle_pig texture link\n";
		return false;
	}
	else
	{
		TEXTURE::Set_Display_Height(JUNGLE_PIG_HEIGHT);
		TEXTURE::Set_Display_Width(JUNGLE_PIG_WIDTH);
		Set_Jungle_Pig_Frame();
		Set_Jungle_Pig_Start_Position(950, 450);
		new_position_x = 950;
		new_position_y = 450;
	}

	if (!Jungle_Pig_Blood.Load_Blood_Texture("GAME_TEXTURE/BLOOD/Jungle_Pig_Blood_Bar.png", screen))
	{
		cout << "error with load blood: fail to load blood texture\n";
		return false;
	}
	else
	{
		Jungle_Pig_Blood.Set_Remain_Blood_Clip(196, 283, 320, 35);
		Jungle_Pig_Blood.Set_Remain_Blood_On_Screen(139, 49, 190, 20);
		Jungle_Pig_Blood.Set_Start_Blood(JUNGLE_PIG_TOTAL_BLOOD);
		Jungle_Pig_Blood.Set_Display_Blood(190);

		Jungle_Pig_Blood.Set_Display_Blood_Bar_Clip(15, 10, 530, 150);
		Jungle_Pig_Blood.Set_Display_Blood_Bar_On_Screen(30, 0, 318, 90);
	}
	return true;
}

void JUNGLEPIG::Handle_Boss_Move()
{
	if (new_position_x > Jungle_Pig_Rect.x)
	{
		Jungle_Pig_Rect.x += JUNGLE_PIG_MOVE_SPEED;
		Jungle_Pig_Collision_Box.x = Jungle_Pig_Rect.x + 58;
		if (Jungle_Pig_Rect.x > new_position_x)
		{
			Jungle_Pig_Rect.x = new_position_x;
			Jungle_Pig_Collision_Box.x = Jungle_Pig_Rect.x + 58;
		}
	}

	if (new_position_x < Jungle_Pig_Rect.x)
	{
		Jungle_Pig_Rect.x -= JUNGLE_PIG_MOVE_SPEED;
		Jungle_Pig_Collision_Box.x = Jungle_Pig_Rect.x + 58;
		if (Jungle_Pig_Rect.x < new_position_x)
		{
			Jungle_Pig_Rect.x = new_position_x;
			Jungle_Pig_Collision_Box.x = Jungle_Pig_Rect.x + 58;
		}
	}

	if (new_position_y > Jungle_Pig_Rect.y)
	{
		Jungle_Pig_Rect.y += JUNGLE_PIG_MOVE_SPEED;
		Jungle_Pig_Collision_Box.y = Jungle_Pig_Rect.y + 100;
		if (Jungle_Pig_Rect.y > new_position_y)
		{
			Jungle_Pig_Rect.y = new_position_y;
			Jungle_Pig_Collision_Box.y = Jungle_Pig_Rect.y + 100;
		}
	}

	if (new_position_y < Jungle_Pig_Rect.y)
	{
		Jungle_Pig_Rect.y -= JUNGLE_PIG_MOVE_SPEED;
		Jungle_Pig_Collision_Box.y = Jungle_Pig_Rect.y + 100;
		if (Jungle_Pig_Rect.y < new_position_y)
		{
			Jungle_Pig_Rect.y = new_position_y;
			Jungle_Pig_Collision_Box.y = Jungle_Pig_Rect.y + 100;
		}
	}

	if (Jungle_Pig_Rect.x == new_position_x && Jungle_Pig_Rect.y == new_position_y) is_jungle_pig_move = false;

}

void JUNGLEPIG::Render_Jungle_Pig(SDL_Renderer* screen, SDL_Rect& camera)
{
	if (check_collision(Jungle_Pig_Rect, camera))
	{
		if (is_jungle_pig_move)
		{
			TEXTURE::render_texture_on_screen(Jungle_Pig_Rect.x - camera.x, Jungle_Pig_Rect.y - camera.y, screen, &Boss_run_frame[frame / 4], 0.0, NULL, boss_look_direction);
			frame++;
			if (frame / 4 >= BOSS_total_run_frame) frame = 0;
		}
		else
		{
			TEXTURE::render_texture_on_screen(Jungle_Pig_Rect.x - camera.x, Jungle_Pig_Rect.y - camera.y, screen, &Boss_idle_frame[frame / 8], 0.0, NULL, boss_look_direction);
			frame++;
			if (frame / 8 >= BOSS_total_idle_frame) frame = 0;
		}
	}
}

void JUNGLEPIG::Render_Jungle_Pig_Blood(SDL_Renderer* screen)
{
	if (Is_Jungle_Pig_Alive)
	{
		Jungle_Pig_Blood.Render_Blood_Bar(screen);
	}
}

void JUNGLEPIG::Generate_New_Position()
{
	new_position_x = rand() % 840 + 520;
	new_position_y = rand() % 520 + 280;

	if (new_position_x < Jungle_Pig_Rect.x) boss_look_direction = SDL_FLIP_HORIZONTAL;
	else if (new_position_x > Jungle_Pig_Rect.x) boss_look_direction = SDL_FLIP_NONE;

	is_jungle_pig_move = true;
}

void JUNGLEPIG::Auto(SDL_Rect player_rect)
{
	if (it_time_to_fight)
	{
		if (SDL_GetTicks() - move_rotTime >= 3000 && is_jungle_pig_move == false)
		{
			move_rotTime = SDL_GetTicks();
			Generate_New_Position();
		}
		else
		{
			Handle_Boss_Move();
		}

		if (SDL_GetTicks() - skills_rotTime >= 3000)
		{
			skills_rotTime = SDL_GetTicks();

			// get random skills
			jungle_pig_skill = rand() % 2 + 1;

			if (jungle_pig_skill == FIRE_BULLET_IN_12_DIRECTION)
			{
				Load_Boss_Bullet_Fire_In_12_Direction();
			}
			else if (jungle_pig_skill == SUMMON_METEO)
			{
				Load_Boss_Meteo();
			}
		}

		// check boss mode to fire bullet
		if (BOSS_MODE == EASY)
		{
			if (SDL_GetTicks() - fire_toward_to_player_rotTime >= 2000)
			{
				fire_toward_to_player_rotTime = SDL_GetTicks();
				Load_Boss_Bullet_Fire_Toward_Player(player_rect);
			}
		}
		else if (BOSS_MODE == MEDIUM)
		{
			if (SDL_GetTicks() - fire_toward_to_player_rotTime >= 1500)
			{
				fire_toward_to_player_rotTime = SDL_GetTicks();
				Load_Boss_Bullet_Fire_Toward_Player(player_rect);
			}
		}
		else if (BOSS_MODE == HARD)
		{
			if (SDL_GetTicks() - fire_toward_to_player_rotTime >= 1000)
			{
				fire_toward_to_player_rotTime = SDL_GetTicks();
				Load_Boss_Bullet_Fire_Toward_Player(player_rect);
			}
		}
	}
	else
	{
		fire_toward_to_player_rotTime = SDL_GetTicks();
		move_rotTime = SDL_GetTicks();
		skills_rotTime = SDL_GetTicks();
	}
}

void JUNGLEPIG::Load_Boss_Bullet_Fire_Toward_Player(SDL_Rect player_rect)
{
	for (int i = 0; i < 5; ++i)
	{
		// create new bullet
		BOSS_BULLET* newBullet = new BOSS_BULLET;

		// set start render point of bullet
		newBullet->Set_start_position(Jungle_Pig_Rect.x + JUNGLE_PIG_WIDTH / 3, Jungle_Pig_Rect.y + JUNGLE_PIG_HEIGHT / 3);

		// set move direction of bullet by using direction vector

		// normalize vector by using equation: V / |V|;
		// with |V| = sqrt(a*a + b*b)
		// after normalize vector has the form (a,b) : 0 <= a <= 1,  0 <= b <= 1

		// get random end vector position in range around player
		int x = rand() % (player_rect.w + 100) + player_rect.x - 50;
		int y = rand() % (player_rect.h + 100) + player_rect.y - 50;

		// normal vector
		Direction_Vector bullet_move_direction = Direction_Vector(float(x - Jungle_Pig_Rect.x - JUNGLE_PIG_WIDTH / 3), float(y - Jungle_Pig_Rect.y - JUNGLE_PIG_HEIGHT / 3));

		// |V|
		float length = bullet_move_direction.Get_Vector_Length();

		// V / |V|
		Direction_Vector nomalize_vector = bullet_move_direction / length;

		// use normalize vector to set bullet move direction
		newBullet->Set_Vector_Move_Direction(nomalize_vector);

		// set bullet moving on screen
		newBullet->Set_Is_Boss_Bullet_Move(true);

		// set bullet moving speed
		newBullet->Set_Bullet_Move_Speed(15);

		// push new bullet to list
		bullet_list.push_back(newBullet);
	}
}

void JUNGLEPIG::Load_Boss_Bullet_Fire_In_12_Direction()
{
	for (int i = 0; i < 12; ++i)
	{
		// create new bullet
		BOSS_BULLET* newBullet = new BOSS_BULLET;

		// set start render point of bullet
		newBullet->Set_start_position(Jungle_Pig_Rect.x + JUNGLE_PIG_WIDTH / 2, Jungle_Pig_Rect.y + JUNGLE_PIG_HEIGHT / 2);

		// set bullet move directon with vector 
		newBullet->Set_Vector_Move_Direction(v[i]);

		// set bullet moving on screen
		newBullet->Set_Is_Boss_Bullet_Move(true);

		// set bullet moving speed
		newBullet->Set_Bullet_Move_Speed(5);

		// push new bullet to list
		bullet_list.push_back(newBullet);
	}
}

void JUNGLEPIG::Load_Boss_Meteo()
{
	// number meteo depend on boss mode
	int number_meteo = 0;
	if (BOSS_MODE == EASY) number_meteo = 5;
	else if (BOSS_MODE == MEDIUM) number_meteo = 7;
	else if (BOSS_MODE == HARD) number_meteo = 10;

	for (int i = 0; i < number_meteo; ++i)
	{
		int x = rand() % 880 + 441;
		int y = rand() % 560 + 401;

		METEO* newMeteo = new METEO;
		newMeteo->Set_Boss_Meteo_Positon(x, y - 1000);
		newMeteo->Set_Boss_Limit(y);
		newMeteo->Set_Is_Boss_Meteo_Falling(true);
		newMeteo->Set_Lava_Position(x - 60, y - 100);
		newMeteo->Set_Lava_Center();
		newMeteo->Set_red_x(x + 40, y - 20);
		meteo_list.push_back(newMeteo);

	}
}

void JUNGLEPIG::Handle_Skills(SDL_Renderer* screen, TILE* tiles[], SDL_Rect& camera)
{
	if (bullet_list.size() >= 1)
	{
		for (int i = 0; i < bullet_list.size(); ++i)
		{
			if (bullet_list[i] != NULL)
			{
				if (bullet_list[i]->Get_Is_Boss_Bullet_Move())
				{
					bullet_list[i]->Handle_Boss_Bullet(tiles);
					bullet_list[i]->Render_Boss_Bullet_On_Screen(screen, camera);
				}
				else
				{
					bullet_list.erase(bullet_list.begin() + i);
				}
			}

		}
	}


	if (meteo_list.size() >= 1)
	{
		for (int i = 0; i < meteo_list.size(); ++i)
		{
			if (meteo_list[i] != NULL)
			{
				if (meteo_list[i]->Get_Is_Boss_Bullet_Falling() && !meteo_list[i]->Get_Is_Create_Lava_Pool())
				{
					meteo_list[i]->handle_meteo();
					meteo_list[i]->render_meteo(screen, camera);
					meteo_list[i]->render_meteo_falling_position(screen, camera);
				}
				else if (!meteo_list[i]->Get_Is_Boss_Bullet_Falling() && meteo_list[i]->Get_Is_Create_Lava_Pool())
				{
					meteo_list[i]->delay_lava_pool();
					meteo_list[i]->render_meteo(screen, camera);
				}
				else if (!meteo_list[i]->Get_Is_Create_Lava_Pool())
				{
					meteo_list.erase(meteo_list.begin() + i);
				}
			}
		}
	}
}

void JUNGLEPIG::Handle_Life(vector<BULLET*> list)
{
	if (!list.empty())
	{
		for (int i = 0; i < list.size(); ++i)
		{
			if (check_collision(list[i]->Get_Bullet_Rect(), Jungle_Pig_Collision_Box))
			{
				list[i]->Set_Is_Bullet_Move(false);
				Jungle_Pig_Blood.Reduce_Blood_By_Damage(BULLET_DAMAGE);
			}
			if (Jungle_Pig_Blood.Get_Current_Blood() <= 0) Set_Is_Alive(false);
		}
	}

	if (Jungle_Pig_Blood.Get_Current_Blood() > JUNGLE_PIG_TOTAL_BLOOD * 2 / 3) BOSS_MODE = EASY;
	else if (Jungle_Pig_Blood.Get_Current_Blood() <= JUNGLE_PIG_TOTAL_BLOOD * 2 / 3) BOSS_MODE = MEDIUM;
	else if (Jungle_Pig_Blood.Get_Current_Blood() <= JUNGLE_PIG_TOTAL_BLOOD / 3) BOSS_MODE = HARD;
}

void JUNGLEPIG::Set_Jungle_Pig_Frame()
{
	Boss_idle_frame[0] = { 196,260,920,800 };
	Boss_idle_frame[1] = { 1040,260,920,800 };
	Boss_idle_frame[2] = { 1915,260,920,800 };
	Boss_idle_frame[3] = { 2830,260,920,800 };

	Boss_run_frame[0] = { 200,2120,920,800 };
	Boss_run_frame[1] = { 1070,2120,920,800 };
	Boss_run_frame[2] = { 1950,2120,920,800 };
	Boss_run_frame[3] = { 2800,2120,920,800 };
	Boss_run_frame[4] = { 3660,2120,920,800 };
	Boss_run_frame[5] = { 4555,2120,920,800 };
	Boss_run_frame[6] = { 5420,2120,920,800 };
	Boss_run_frame[7] = { 6275,2120,920,800 };
}

void JUNGLEPIG::Clear_Boss()
{
	Jungle_Pig_Rect = { 0,0,0, 0 };
	Jungle_Pig_Collision_Box = { 0,0,0,0 };
	frame = 0;
	boss_look_direction = SDL_FLIP_HORIZONTAL;

	new_position_x = 0; new_position_y = 0;
	is_jungle_pig_move = false;

	jungle_pig_skill = 0;

	skills_rotTime = 0;
	move_rotTime = 0;

	it_time_to_fight = false;
	Is_Jungle_Pig_Alive = false;

	bullet_list.clear();
	meteo_list.clear();
}

void JUNGLEPIG::Reset_From_Start()
{
	Jungle_Pig_Rect = { 0,0,JUNGLE_PIG_WIDTH, JUNGLE_PIG_HEIGHT };
	Jungle_Pig_Collision_Box = { 0,0,145,90 };

	Set_Jungle_Pig_Start_Position(950, 450);
	new_position_x = 950;
	new_position_y = 450;

	Jungle_Pig_Blood.Reset_Blood();

	is_jungle_pig_move = false;

	Set_It_Time_To_Fight(false);
	Set_Is_Alive(true);

	meteo_list.clear();
	bullet_list.clear();
}