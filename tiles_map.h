#pragma once

#include "texture.h"

const int LEVEL1_WIDTH = 2000;
const int LEVEL1_HEIGHT = 1200;
const int TILE_SIZE = 40;
const int TOTAL_TILE_LEVEL_1 = 1500;

const int TOTAL_TILE_TYPE = 8;
static SDL_Rect tile_sprite[TOTAL_TILE_TYPE];

const int FLOOR_PATH = 0;
const int FLOOR_WITH_SHADOW_PATH = 1;
const int WALL_SIDE_PATH = 2;
const int WALL_TOP_PATH = 3;
const int GATE_WAY_PATH = 4;
const int GATE_WAY_WITH_SHADOW_PATH = 5;
const int CORNER_PATH = 6;
const int BLACK_PATH = 7;

const int total_gate_tile_level1 = 10;
static int gate_level_1[total_gate_tile_level1] = { 660,689,710,739,760,789,810,839,860,889 };

static SDL_Rect play_area_level_1 = { 480,280,760,1160 };
static SDL_Rect get_win_area_level_1 = { 1600,560,240,160 };


class TILE
{
public:
	TILE(const int& x, const int& y, const int& tileType);

	~TILE();

	void render_tile(SDL_Rect& camera, SDL_Renderer* screen);

	void set_tile_type(const int& val) { mType = val; }

	SDL_Rect get_mPath() const { return mPath; }

	int get_tile_type() const { return mType; }

private:
	SDL_Rect mPath;
	int mType;
};

static TEXTURE map_texture;

static TILE* map1[TOTAL_TILE_LEVEL_1];

bool load_map_texture(string path, SDL_Renderer* screen);

void close_gate_level_1(TILE* map[], int gate[]);

void open_gate_level_1(TILE* map[], int gate[]);

bool player_in_play_area(SDL_Rect player);

bool player_in_win_area(SDL_Rect player);

bool set_tile_map_level_1(TILE* tiles[], string path);

bool load_map_level_1(TILE* tiles[], SDL_Renderer* screen);