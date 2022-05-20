#pragma once

#include "texture.h"
#include "tiles_map.h"
#include "jungle_pig_skills.h"
#include "blood.h"
#include "bullet.h"

const Uint32 delay_get_skills_period = 1500;
const Uint32 delay_move_period = 2000;
const int JUNGLE_PIG_MOVE_SPEED = 15;

const int JUNGLE_PIG_WIDTH = 240;
const int JUNGLE_PIG_HEIGHT = 240;

const int BOSS_total_idle_frame = 4;
const int BOSS_total_run_frame = 8;
static SDL_Rect BOSS_idle_frame[BOSS_total_idle_frame];
static SDL_Rect BOSS_run_frame[BOSS_total_run_frame];

enum BOSS_MODE
{
	EASY = 11,
	MEDIUM = 21,
	HARD = 31
};

static Direction_Vector v[12]
{
	Direction_Vector(1.0,0.0),
	Direction_Vector(0.0,1.0),
	Direction_Vector(-1.0,0.0),
	Direction_Vector(0.0,-1.0),
	Direction_Vector(0.44f,0.89f),
	Direction_Vector(0.89f,0.44f),
	Direction_Vector(-0.89f,0.44f),
	Direction_Vector(-0.44f,0.89f),
	Direction_Vector(-0.89f,-0.44f),
	Direction_Vector(-0.44f,-0.89f),
	Direction_Vector(0.89f,-0.44f),
	Direction_Vector(0.44f,-0.89f)
};

enum BOSS_SKILL
{
	FIRE_BULLET_IN_12_DIRECTION = 1,
	SUMMON_METEO = 2,
};

class JUNGLEPIG : public TEXTURE
{
public:
	JUNGLEPIG();

	~JUNGLEPIG();

	bool Load_Jungle_Pig_Texture(SDL_Renderer* screen);

	void Handle_Boss_Move();

	void Render_Jungle_Pig(SDL_Renderer* screen, SDL_Rect& camera);

	void Render_Jungle_Pig_Blood(SDL_Renderer* screen);

	void Generate_New_Position();

	void Auto(SDL_Rect player_rect);

	void Load_Boss_Bullet_Fire_Toward_Player(SDL_Rect player_rect);

	void Load_Boss_Bullet_Fire_In_12_Direction();

	void Load_Boss_Meteo();

	void Handle_Skills(SDL_Renderer* screen, TILE* tiles[], SDL_Rect& camera);

	void Handle_Life(vector<BULLET*> list);

	void Set_Is_Alive(const bool& val) { Is_Jungle_Pig_Alive = val; }

	void Set_Jungle_Pig_Start_To_Fight(const bool& val) { it_time_to_fight = val; }

	void Set_Jungle_Pig_Frame();

	void Set_Jungle_Pig_Start_Position(const int& x, const int& y)
	{
		Jungle_Pig_Rect.x = x; Jungle_Pig_Rect.y = y;
		Jungle_Pig_Collision_Box.x = x + 50; Jungle_Pig_Collision_Box.y = y + 100;
	}

	void Set_It_Time_To_Fight(const bool& val) { it_time_to_fight = val; }

	void Clear_Boss();

	bool Get_Is_Jungle_Pig_Alive() const { return Is_Jungle_Pig_Alive; }

	SDL_Rect Get_Jungle_Pig_Rect() const { return Jungle_Pig_Rect; }

	SDL_Rect Get_Jungle_Pig_Collision_Box() const { return Jungle_Pig_Collision_Box; }

	vector<BOSS_BULLET*> Get_Bullet_List() const { return bullet_list; }

	vector<METEO*> Get_Meteo_List() const { return meteo_list; }

	void Reset_From_Start();
private:
	SDL_Rect Jungle_Pig_Rect, Jungle_Pig_Collision_Box;
	int frame;
	SDL_RendererFlip boss_look_direction;

	BLOOD Jungle_Pig_Blood;

	int new_position_x, new_position_y;
	bool is_jungle_pig_move;

	int jungle_pig_skill;
	Uint32 skills_rotTime;
	Uint32 move_rotTime;
	Uint32 fire_toward_to_player_rotTime;
	int BOSS_MODE;

	bool it_time_to_fight;
	bool Is_Jungle_Pig_Alive;

	vector<BOSS_BULLET*> bullet_list;
	vector<METEO*> meteo_list;
};



static JUNGLEPIG main_Jungle_Pig;