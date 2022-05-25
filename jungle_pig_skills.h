#pragma once

#include <vector>

#include "texture.h"
#include "tiles_map.h"
#include "direction_Vector.h"

// fire bullet skill

const int BOSS_BULLET_DISPLAY_WIDTH = 60;
const int BOSS_BULLET_DISPLAY_HEIGHT = 60;
const int BOSS_BULLET_DAMAGE = 20;
static TEXTURE boss_bullet_texture;

class BOSS_BULLET
{
public:
	BOSS_BULLET();

	~BOSS_BULLET();

	void Handle_Boss_Bullet(TILE* tiles[]);

	void Render_Boss_Bullet_On_Screen(SDL_Renderer* screen, SDL_Rect& camera);

	void Set_start_position(const int& x, const int& y) { boss_bullet_rect.x = x; boss_bullet_rect.y = y; }

	void Set_Vector_Move_Direction(const Direction_Vector& in_vector) { move_direction = in_vector; }

	void Set_Is_Boss_Bullet_Move(const bool& val) { is_bullet_move = val; }

	void Set_Bullet_Move_Speed(const int& val) { BOSS_BULLET_MOVE_SPEED = val; }

	SDL_Rect Get_Boss_Bullet_Rect() const { return boss_bullet_rect; }

	bool Get_Is_Boss_Bullet_Move() const { return is_bullet_move; }
private:
	SDL_Rect boss_bullet_rect;
	bool is_bullet_move;
	
	int BOSS_BULLET_MOVE_SPEED;
	
	Direction_Vector move_direction;
};



bool Load_Jungle_Pig_Bullet_Texture(SDL_Renderer* screen);






// summon meteo skill

const int METEO_WIDTH = 120;
const int METEO_HEIGHT = 250;
const int METEO_total_frame = 18;
static SDL_Rect Meteo_frame[METEO_total_frame];
const int METEO_SPEED = 10;

const int LAVA_SIZE = 240;
const double LAVA_RADIUS = 120.0;
const int RED_X_SIZE = 40;
const int LAVA_DAMAGE = 20;

static TEXTURE Meteo_Texture;
static TEXTURE Lava_Texuture;
static TEXTURE red_x_texture;

class METEO
{
public:

	METEO();
	~METEO();

	void Set_Boss_Meteo_Positon(const int& x, const int& y) { METEO_POS.x = x; METEO_POS.y = y; }

	void Set_Is_Boss_Meteo_Falling(const bool& val) { Is_Boss_Meteo_Falling = val; }

	void Set_Boss_Limit(const int& val) { Limit = val; }

	void Set_Is_Create_Lava_Pool(const bool& val) { Is_Create_Lava_Pool = val; }

	void Set_Lava_Position(const int& x, const int& y) { LAVA_POS.x = x; LAVA_POS.y = y; }

	void Set_red_x(const int& x, const int& y) { red_x_pos.x = x; red_x_pos.y = y; }

	void Set_Lava_Center() { lava_center_x = LAVA_POS.x + LAVA_SIZE / 2; lava_center_y = LAVA_POS.y + 20; }




	int Get_Boss_Bullet_x() const { return METEO_POS.x; }

	int Get_Boss_Bullet_y() const { return METEO_POS.y; }

	bool Get_Is_Boss_Bullet_Falling() const { return Is_Boss_Meteo_Falling; }

	bool Get_Is_Create_Lava_Pool()  const { return Is_Create_Lava_Pool; }

	int Get_Lava_Center_x() const { return lava_center_x; }

	int Get_Lava_Center_y() const { return lava_center_y; }


	void handle_meteo();

	void render_meteo(SDL_Renderer* screen, SDL_Rect& camera);



	void render_meteo_falling_position(SDL_Renderer* screen, SDL_Rect& camera);

	void delay_lava_pool();

	bool delay_damage();
private:
	SDL_Rect METEO_POS;
	bool Is_Boss_Meteo_Falling;

	SDL_Rect LAVA_POS;
	SDL_Rect red_x_pos;

	bool Is_Create_Lava_Pool;
	int Limit;
	int lava_center_x, lava_center_y;
	bool is_get_time;
	Uint32 rotTime;
	Uint32 delay_damage_time;
	int frame;
};

bool load_jungle_pig_skill_texture(SDL_Renderer* screen);
