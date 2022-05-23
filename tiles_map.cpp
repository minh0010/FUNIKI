#include <fstream>

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
	if (!map_texture.load_texture_from_file(path, screen))
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

	return true;
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

bool set_tile_map_level_1(TILE* tiles[], string path)
{
	fstream file;
	file.open(path);

	if (!file.is_open())
	{
		cout << "fail to open file map";
		return false;
	}
	else
	{
		int k = 0;
		for (int i = 0; i < LEVEL1_HEIGHT; i += TILE_SIZE)
		{
			for (int j = 0; j < LEVEL1_WIDTH; j += TILE_SIZE)
			{
				int tile_type = -1;
				file >> tile_type;
				if (file.fail())
				{
					cout << "error loading map: file not found\n";
					return false;
				}
				else
				{
					if (tile_type >= FLOOR_PATH && tile_type <= BLACK_PATH)
					{
						tiles[k] = new TILE(j, i, tile_type);
						++k;
					}
					else
					{
						cout << "error loading map: invalid tile type\n";
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool load_map_level_1(TILE* tiles[], SDL_Renderer* screen)
{
	if (!load_map_texture("GAME_TEXTURE/GAME_MAP/path.png", screen))
	{
		cout << "Error with load map: fail to load map texture level 1 texture\n";
		return false;
	}
	else
	{
		if (!set_tile_map_level_1(tiles, "GAME_TEXTURE/GAME_MAP/map_level1.txt"))
		{
			cout << "Error with load map: fail to load map file level 1 texture\n";
			return false;
		}
	}
	return true;
}