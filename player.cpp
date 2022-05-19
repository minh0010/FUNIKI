#include <iostream>
#include <math.h>


#include "player.h"

#include "function.h"
#include "Direction_Vector.h"

REAPER::REAPER()
{
	Reaper_Rect = { 0,0,REAPER_WIDTH,REAPER_HEIGHT };
	Reaper_Collision_Box = { 0,0,25,55 };
	Reaper_Velx = 0;
	Reaper_Vely = 0;

	Is_Reaper_Move = false;
	Is_Reaper_Alive = true;

	Frame = 0;

	Reaper_look_direction = SDL_FLIP_NONE;

	fire_bullet_effect = NULL;
}

REAPER::~REAPER()
{
	TEXTURE::free();
}

bool REAPER::Load_Reaper_From_File(SDL_Renderer* screen)
{
	// load display character when play game
	if (!TEXTURE::load_texture_from_file("GAME_TEXTURE/REAPER_TEXTURE/reaper.png", screen, true, 20, 35, 38))
	{
		cout << "- Fail to load main character from file\n";
		return false;
	}
	else
	{
		Set_Display_Width(REAPER_WIDTH);
		Set_Display_Height(REAPER_HEIGHT);
		Set_Reaper_Frame();

		Set_Start_Position(200, 540);
	}


	// load display blood of character when play game
	if (!Reaper_Blood.Load_Blood_Texture("GAME_TEXTURE/BLOOD/Reaper_Blood_Bar.png", screen))
	{
		cout << "- Fail to load blood texture from file\n";
		return false;
	}
	else
	{
		Reaper_Blood.Set_Remain_Blood_Clip(156, 234, 350, 50);
		Reaper_Blood.Set_Remain_Blood_On_Screen(97, 610, 146, 28);
		Reaper_Blood.Set_Start_Blood(REAPER_TOTAL_BLOOD);
		Reaper_Blood.Set_Display_Blood(146);

		Reaper_Blood.Set_Display_Blood_Bar_Clip(45, 40, 480, 115);
		Reaper_Blood.Set_Display_Blood_Bar_On_Screen(50, 590, 200, 64);
	}


	// fire bullet sound when ever user click mouse
	fire_bullet_effect = Mix_LoadWAV("SOUND_EFFECT_AND_MUSIC/fire_bullet.wav");
	if (fire_bullet_effect == NULL)
	{
		cout << "- Fail to load main character fire bullet effect\n";
		return false;
	}
	else
	{
		Mix_VolumeChunk(fire_bullet_effect, 32);
	}


	// load display gun for player
	if (!Reaper_Gun.Load_Gun_Texture(screen))
	{
		cout << "- Fail to load main character weapon - Gun\n";
		return false;
	}
	return true;
}

void REAPER::Handle_Reaper(SDL_Event& e, SDL_Rect& camera)
{
	// determined that player alive or not
	if (Is_Reaper_Alive)
	{
		// when the keyboard is pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w: Reaper_Vely -= REAPER_MOVE_SPEED; Is_Reaper_Move = true; Frame = 0; break;
			case SDLK_s: Reaper_Vely += REAPER_MOVE_SPEED; Is_Reaper_Move = true; Frame = 0; break;
			case SDLK_a: Reaper_Velx -= REAPER_MOVE_SPEED; Is_Reaper_Move = true; Frame = 0; break;
			case SDLK_d: Reaper_Velx += REAPER_MOVE_SPEED; Is_Reaper_Move = true; Frame = 0; break;
			}
		}
		// when the keyboard is released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w: Reaper_Vely += REAPER_MOVE_SPEED; Is_Reaper_Move = false; break;
			case SDLK_s: Reaper_Vely -= REAPER_MOVE_SPEED; Is_Reaper_Move = false; break;
			case SDLK_a: Reaper_Velx += REAPER_MOVE_SPEED; Is_Reaper_Move = false; break;
			case SDLK_d: Reaper_Velx -= REAPER_MOVE_SPEED; Is_Reaper_Move = false; break;
			}

		}
		// when click mouse
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			BULLET* newBullet = new BULLET;

			// set start fire bullet position
			newBullet->Set_start_position(Reaper_Rect.x + REAPER_WIDTH / 2, Reaper_Rect.y + 78);

			// get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);


			// set move direction of bullet by using direction vector
			
			// normalize vector by using equation: V / |V|;
			// with |V| = sqrt(a*a + b*b)
			// after normalize vector has the form (a,b) : 0 <= a <= 1,  0 <= b <= 1

			// normal vector
			Direction_Vector bullet_fire_direction((float)(x - (Reaper_Rect.x + REAPER_WIDTH / 2.0 - camera.x)), (float)(y - (Reaper_Rect.y + 78 - camera.y)));

			// |V|
			float length = bullet_fire_direction.Get_Vector_Length();

			// V / |V|
			Direction_Vector nomalize_vector = bullet_fire_direction / length;

			// use normalize vector to set bullet move direction
			newBullet->Set_Vector_Move_Direction(nomalize_vector);

			// set bullet move on screen value = true
			newBullet->Set_Is_Bullet_Move(true);

			// add new bullet to list
			reaper_bullet_list.push_back(newBullet);

			// make fire bullet sound
			Mix_PlayChannel(-1, fire_bullet_effect, 0);
		}


		// determined turn direction of player relative to the mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < Reaper_Rect.x - camera.x)
		{
			Reaper_look_direction = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			Reaper_look_direction = SDL_FLIP_NONE;
		}
	}
	else return;
}

void REAPER::Handle_gun(SDL_Rect& camera)
{
	// set gun position when player turn to the right
	if (Reaper_look_direction == SDL_FLIP_NONE)
	{
		Reaper_Gun.set_rect(Reaper_Rect.x - camera.x + 35, Reaper_Rect.y - camera.y + 65);
	}
	else if (Reaper_look_direction == SDL_FLIP_HORIZONTAL)
	{
		Reaper_Gun.set_rect(Reaper_Rect.x - camera.x + 28, Reaper_Rect.y - camera.y + 65);
	}

	// update neư rotation angle of gun relavtie to the mouse position
	Reaper_Gun.Update(camera);
}

void REAPER::Set_Reaper_Camera(SDL_Rect& camera)
{
	// center the camera
	camera.x = (Reaper_Rect.x + REAPER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (Reaper_Rect.y + REAPER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	// Determine if the camera is at the boundary
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > LEVEL1_WIDTH - camera.w) camera.x = LEVEL1_WIDTH - camera.w;
	if (camera.y > LEVEL1_HEIGHT - camera.h) camera.y = LEVEL1_HEIGHT - camera.h;
}

void REAPER::Reaper_Move(TILE* tiles[])
{
	// increase player x
	Reaper_Rect.x += Reaper_Velx;
	Reaper_Collision_Box.x = Reaper_Rect.x + 37;

	// determine if the player encounters an obstacle
	if (touch_wall(Reaper_Collision_Box, tiles))
	{
		Reaper_Rect.x -= Reaper_Velx;
		Reaper_Collision_Box.x = Reaper_Rect.x + 37;
	}

	// increase player y
	Reaper_Rect.y += Reaper_Vely;
	Reaper_Collision_Box.y = Reaper_Rect.y + 43;

	// determine if the player encounters an obstacle
	if (touch_wall(Reaper_Collision_Box, tiles))
	{
		Reaper_Rect.y -= Reaper_Vely;
		Reaper_Collision_Box.y = Reaper_Rect.y + 43;
	}
}

void REAPER::Render_Reaper_On_Screen(SDL_Renderer* screen, SDL_Rect& camera)
{
	if (Is_Reaper_Move)
	{
		TEXTURE::render_texture_on_screen(Reaper_Rect.x - camera.x, Reaper_Rect.y - camera.y, screen, &Reaper_Running_frame[Frame / 2], 0.0, NULL, Reaper_look_direction);
		Frame++;
		if (Frame / 2 >= Reaper_number_runing_frame) Frame = 0;
	}
	else if (!Is_Reaper_Move)
	{
		TEXTURE::render_texture_on_screen(Reaper_Rect.x - camera.x, Reaper_Rect.y - camera.y, screen, &Reaper_Idle_frame[Frame / 3], 0.0, NULL, Reaper_look_direction);
		Frame++;
		if (Frame / 3 >= Reaper_number_idle_frame) Frame = 0;
	}
}

void REAPER::Render_Reaper_Gun(SDL_Renderer* screen)
{
	Reaper_Gun.Render_Gun(screen);
}

void REAPER::Render_Reaper_Blood(SDL_Renderer* screen)
{
	Reaper_Blood.Render_Blood_Bar(screen);
}

void REAPER::Handle_Bullet_List(SDL_Renderer* screen, SDL_Rect& camera, TILE* tiles[], SDL_Rect boss_rect)
{
	// determined bullet list are empty or not
	if (reaper_bullet_list.size() >= 1)
	{
		for (int i = 0; i < reaper_bullet_list.size(); ++i)
		{
			if (reaper_bullet_list[i] != NULL)
			{
				// check bullet still moving on screen
				if (reaper_bullet_list[i]->Get_Is_Bullet_Move())
				{
					reaper_bullet_list[i]->Handle_Bullet(tiles);
					reaper_bullet_list[i]->Render_Bullet_On_Screen(screen, camera);
				}
				else
				{
					reaper_bullet_list.erase(reaper_bullet_list.begin() + i);
				}
			}
		}
	}
}

void REAPER::Handle_Reaper_Life(vector<BOSS_BULLET*> jungle_pig_bullet_list, vector<METEO*> jungle_pig_meteo_list)
{
	if (jungle_pig_bullet_list.size() >= 1)
	{
		for (int i = 0; i < jungle_pig_bullet_list.size(); ++i)
		{
			if (jungle_pig_bullet_list[i] != NULL)
			{
				// when there is a collision with an bullet, reduce player blood 
				if (check_collision(jungle_pig_bullet_list[i]->Get_BOSS_BULLET_Rect(), Reaper_Collision_Box))
				{
					Reaper_Blood.Reduce_Blood_By_Damage(BOSS_BULLET_DAMAGE);
					jungle_pig_bullet_list[i]->Set_Is_BOSS_BULLET_Move(false);
					if (Reaper_Blood.Get_Current_Blood() <= 0) Is_Reaper_Alive = false;
				}
			}
		}
	}

	if (jungle_pig_meteo_list.size() >= 1)
	{
		for (int i = 0; i < jungle_pig_meteo_list.size(); ++i)
		{
			if (jungle_pig_meteo_list[i] != NULL)
			{
				// get lava center
				int x = jungle_pig_meteo_list[i]->Get_Lava_Center_x();
				int y = jungle_pig_meteo_list[i]->Get_Lava_Center_y();

				// determined player are in lava zone or not
				double distance = sqrt((double)pow(x - Reaper_Rect.x, 2) + (double)pow(y - Reaper_Rect.y, 2));

				// when player distance from player position to lava center lower than lava radius, reduce player blood 
				if (distance < LAVA_RADIUS && !jungle_pig_meteo_list[i]->delay_damage())
				{
					Reaper_Blood.Reduce_Blood_By_Damage(LAVA_DAMAGE);
					if (Reaper_Blood.Get_Current_Blood() <= 0) Is_Reaper_Alive = false;
				}
			}
		}
	}
}

void REAPER::Set_Reaper_Frame()
{
	// set player standing frames
	for (int i = 0; i < Reaper_number_idle_frame; ++i)
	{
		Reaper_Idle_frame[i] = { 270 * i,0,270,270 };
	}

	// set player when moving frames
	for (int i = 0; i < Reaper_number_runing_frame; ++i)
	{
		Reaper_Running_frame[i] = { 270 * i,270,270,270 };
	}
}

void REAPER::Reset_From_Start()
{
	Set_Start_Position(200, 540);
	Reaper_Velx = 0;
	Reaper_Vely = 0;

	Is_Reaper_Move = false;
	Is_Reaper_Alive = true;
	Reaper_Blood.Reset_Blood();

	reaper_bullet_list.clear();
}