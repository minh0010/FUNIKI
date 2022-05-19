#pragma once

#include <string>
#include <vector>

#include <SDL_mixer.h>

#include "texture.h"
#include "tiles_map.h"
#include "bullet.h"
#include "blood.h"
#include "jungle_pig_skills.h"
#include "gun.h"



const int REAPER_WIDTH = 100;
const int REAPER_HEIGHT = 120;
const int REAPER_MOVE_SPEED = 8;

const int Reaper_number_idle_frame = 18;
const int Reaper_number_runing_frame = 12;
const int Reaper_number_throwing_frame = 12;
const int Reaper_number_dying_frame = 15;

static SDL_Rect Reaper_Idle_frame[Reaper_number_idle_frame];
static SDL_Rect Reaper_Running_frame[Reaper_number_runing_frame];
static SDL_Rect Reaper_Throwing_frame[Reaper_number_throwing_frame];
static SDL_Rect Reaper_Dying_frame[Reaper_number_dying_frame];

class REAPER : public TEXTURE
{
public:
	REAPER();
	~REAPER();

	bool Load_Reaper_From_File(SDL_Renderer* screen);

	void Handle_Reaper(SDL_Event& e, SDL_Rect& camera);

	void Handle_gun(SDL_Rect& camera);

	void Set_Reaper_Camera(SDL_Rect& camera);

	void Reaper_Move(TILE* tiles[]);




	void Render_Reaper_On_Screen(SDL_Renderer* screen, SDL_Rect& camera);

	void Render_Reaper_Gun(SDL_Renderer* screen);

	void Render_Reaper_Blood(SDL_Renderer* screen);

	void Handle_Bullet_List(SDL_Renderer* screen, SDL_Rect& camera, TILE* tiles[], SDL_Rect boss_rect);



	void Handle_Reaper_Life(vector<BOSS_BULLET*> jungle_pig_bullet_list, vector<METEO*> jungle_pig_meteo_list);

	void Set_Reaper_Frame();

	void Set_Start_Position(const int& x, const int& y) { Reaper_Rect.x = x; Reaper_Rect.y = y; }

	void Set_Is_Reaper_Alive(const bool& val) { Is_Reaper_Alive = val; }





	SDL_Rect Get_Reaper_Rect() const { return Reaper_Rect; }

	int Get_Reaper_Render_Pos_x() const { return Reaper_Rect.x; }

	int Get_Reaper_Render_Pos_y() const { return Reaper_Rect.y; }

	bool Get_Is_Reaper_Alive() const { return Is_Reaper_Alive; }

	SDL_Rect Get_Reaper_Collision_Box() const { return Reaper_Collision_Box; }

	vector<BULLET*> Get_Bullet_List() const { return reaper_bullet_list; }




	void Reset_From_Start();

private:
	SDL_Rect Reaper_Rect, Reaper_Collision_Box;
	int Reaper_Velx, Reaper_Vely;
	int Frame;

	bool Is_Reaper_Alive;

	BLOOD Reaper_Blood;

	bool Is_Reaper_Move;

	SDL_RendererFlip Reaper_look_direction;

	Gun Reaper_Gun;

	vector<BULLET*> reaper_bullet_list;
	Mix_Chunk* fire_bullet_effect;
};



static REAPER main_Reaper;