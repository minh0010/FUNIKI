#include "tiles_map.h"
#include "function.h"

TILE::TILE(const int& x, const int& y, const int& tileType)
{
	mPath = { x,y,TILE_SIZE, TILE_SIZE };
	mType = tileType;
}

TILE::~TILE()
{

}

void TILE::render_tile(SDL_Rect& camera, SDL_Renderer* screen)
{
	if (check_collision(mPath, camera))
	{
		map_texture.render_texture_on_screen(mPath.x - camera.x, mPath.y - camera.y, screen, &tile_sprite[mType]);
	}
	else return;
}


bool load_map_texture(string path, SDL_Renderer* screen)
{
	bool load = map_texture.load_texture_from_file(path, screen);
	if (!load)
	{
		return false;
	}
	else
	{
		map_texture.Set_Display_Height(TILE_SIZE);
		map_texture.Set_Display_Width(TILE_SIZE);
		tile_sprite[0] = { 0,0,32,32 };
		tile_sprite[1] = { 32,0,32,32 };
		tile_sprite[2] = { 64,0,31,31 };
		tile_sprite[3] = { 96,0,32,32 };
		tile_sprite[4] = { 128,0,32,32 };
		tile_sprite[5] = { 160,0,32,32 };
		tile_sprite[6] = { 192,0,32,32 };
		tile_sprite[7] = { 224,0,32,32 };
	}
	return load;
}

void close_gate_level_1(TILE* map[], int gate[])
{
	for (int i = 0; i < total_gate_tile_level1; ++i)
	{
		map[gate[i]]->set_tile_type(WALL_TOP_PATH);
	}
}

void open_gate_level_1(TILE* map[], int gate[])
{
	for (int i = 0; i < total_gate_tile_level1; ++i)
	{
		if (i == 0 || i == 1) map[gate[i]]->set_tile_type(CORNER_PATH);
		else if (i == 2 || i == 3) map[gate[i]]->set_tile_type(GATE_WAY_WITH_SHADOW_PATH);
		else map[gate[i]]->set_tile_type(GATE_WAY_PATH);
	}
}

bool player_in_play_area(SDL_Rect player)
{
	if (check_collision(player, play_area_level_1))
	{
		return true;
	}
	return false;
}

bool player_in_win_area(SDL_Rect player)
{
	if (check_collision(player, get_win_area_level_1))
	{
		return true;
	}
	return false;
}