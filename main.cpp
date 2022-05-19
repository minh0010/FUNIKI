#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

#include "texture.h"
#include "tiles_map.h"
#include "blood.h"
#include "jungle_pig_boss.h"
#include "player.h"
#include "function.h"
#include "game_display.h"


SDL_Window* WINDOW = NULL;
SDL_Renderer* RENDER = NULL;


const string map1_path_to_file = "GAME_TEXTURE/GAME_MAP/map_level1.txt";
const string map1_path_to_texture = "GAME_TEXTURE/GAME_MAP/path.png";

bool init();

bool load_media();

void close(TILE* tiles[]);

bool set_tile_map_level_1(TILE* tiles[], string path);

bool load_map_level_1(TILE* tiles[]);

void reload_game();

int main(int arv, char* argc[])
{
	if (!init())
	{
		cout << "error with function: fail at init(...)\n";
		return 0;
	}

	if (!load_media())
	{
		cout << "error with function: fail at load_media(...)\n";
		return 0;
	}

	bool quit = false;
	SDL_Event e;
	SDL_Rect camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	srand((unsigned int)time(NULL));

	Uint32 timemm = 0;

	while (!quit)
	{
		FUNIKI_MENU.Handle_sound();
		if (FUNIKI_MENU.Get_Request_A_Reload())
		{
			reload_game();
			FUNIKI_MENU.Set_Request_A_Reload(false);
		}

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			FUNIKI_MENU.Handle_All_Button(e, quit);

			if (FUNIKI_MENU.Get_Screen_Status() == PLAY_SCREEN)
			{
				main_Reaper.Handle_Reaper(e, camera);
			}
		}

		SDL_SetRenderDrawColor(RENDER, 40, 40, 40, 255);
		SDL_RenderClear(RENDER);

		FUNIKI_MENU.Render_Background(RENDER);

		if (FUNIKI_MENU.Get_Screen_Status() == PLAY_SCREEN)
		{
			for (int i = 0; i < TOTAL_TILE_LEVEL_1; ++i) map1[i]->render_tile(camera, RENDER);


			// ingame boss 
			if (main_Jungle_Pig.Get_Is_Jungle_Pig_Alive())
			{
				if (player_in_play_area(main_Reaper.Get_Reaper_Collision_Box()))
				{
					main_Jungle_Pig.Set_It_Time_To_Fight(true);
					close_gate_level_1(map1, gate_level_1);
				}

				main_Jungle_Pig.Handle_Skills(RENDER, map1, camera);
				main_Jungle_Pig.Auto();
				main_Jungle_Pig.Render_Jungle_Pig(RENDER, camera);
				main_Jungle_Pig.Render_Jungle_Pig_Blood(RENDER);

				if (player_in_play_area(main_Reaper.Get_Reaper_Collision_Box()))
				{
					main_Jungle_Pig.Handle_Life(main_Reaper.Get_Bullet_List());
				}
			}
			else
			{
				main_Jungle_Pig.Clear_Boss();
				open_gate_level_1(map1, gate_level_1);
			}


			// ingame player
			if (main_Reaper.Get_Is_Reaper_Alive())
			{
				main_Reaper.Handle_gun(camera);
				main_Reaper.Reaper_Move(map1);
				main_Reaper.Set_Reaper_Camera(camera);

				main_Reaper.Handle_Reaper_Life(main_Jungle_Pig.Get_Bullet_List(), main_Jungle_Pig.Get_Meteo_List());

				main_Reaper.Render_Reaper_On_Screen(RENDER, camera);
				main_Reaper.Handle_Bullet_List(RENDER, camera, map1, main_Jungle_Pig.Get_Jungle_Pig_Collision_Box());
				main_Reaper.Render_Reaper_Gun(RENDER);
				main_Reaper.Render_Reaper_Blood(RENDER);

				if (player_in_win_area(main_Reaper.Get_Reaper_Collision_Box()))
				{
					FUNIKI_MENU.Set_Screen_Status(SCREEN_AFTER_WIN);
					FUNIKI_MENU.Set_Screen_After_Win();
					FUNIKI_MENU.Set_Request_A_Reload(true);
				}
			}
			else
			{
				FUNIKI_MENU.Set_Screen_Status(SCREEN_AFTER_LOSE);
				FUNIKI_MENU.Set_Screen_After_Lose();
				FUNIKI_MENU.Set_Request_A_Reload(true);
			}
		}

		FUNIKI_MENU.Render_Menu_Button(RENDER);
		mouse.Render_Mouse(RENDER);

		SDL_RenderPresent(RENDER);
	}

	close(map1);
	system("pause");
	return 0;
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL error: fail at SDL_Init(...)\n";
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout << "SDL error: fail at SDL_SetHint(...)\n";
		return false;
	}

	WINDOW = SDL_CreateWindow("FUNIKI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (WINDOW == NULL)
	{
		cout << "SDL error: can not use SDL_CreateWindow(...)\n";
		return false;
	}

	RENDER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (RENDER == NULL)
	{
		cout << "SDL error: can not use SDL_CreateRenderer(...)\n";
		return false;
	}

	int png = IMG_INIT_PNG;
	if (!(IMG_Init(png) & png))
	{
		cout << "SDL error: can not use IMG_Init(...)\n";
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: Mix_GetError()\n";
		return false;
	}

	if (TTF_Init() == -1)
	{
		cout << "SDL_ttf could not initialize! SDL_ttf Error: TTF_GetError\n";
		return false;
	}

	return true;
}

bool load_media()
{
	// load game font
	if (!Load_Game_Font())
	{
		return false;
	}


	// load tile map level 1 
	if (!load_map_level_1(map1))
	{
		cout << "error with load map level 1: \n";
		return false;
	}


	// load boss level 1 - jungle_pig
	if (!main_Jungle_Pig.Load_Jungle_Pig_Texture(RENDER))
	{
		cout << "fail to load main jungle pig texture from file\n";
		return false;
	}

	if (!Load_Jungle_Pig_Bullet_Texture(RENDER))
	{
		cout << "fail to load boss bullet\n";
		return false;
	}

	if (!load_jungle_pig_skill_texture(RENDER))
	{
		return false;
	}


	// load player character 
	if (!main_Reaper.Load_Reaper_From_File(RENDER))
	{
		cout << "Error with load main character texture:\n";
		return false;
	}

	if (!Load_Bullet_Texture(RENDER))
	{
		cout << "Error with load bullet texture:\n";
		return false;
	}

	// load game menu
	if (!FUNIKI_MENU.Load_All_Button_And_Background_Display(RENDER))
	{
		cout << "error with load FUNIKI_MENU" << endl;
		return false;
	}

	if (!FUNIKI_MENU.load_sound_effect_and_music())
	{
		cout << "error with load game sound effect and music:\n";
		return false;
	}

	if (!mouse.Load_Mouse_Texture(RENDER))
	{
		return false;
	}

	return true;
}

void close(TILE* tiles[])
{
	for (int i = 0; i < TOTAL_TILE_LEVEL_1; ++i)
	{
		delete tiles[i];
		tiles[i] = NULL;
	}

	SDL_DestroyRenderer(RENDER);
	SDL_DestroyWindow(WINDOW);

	RENDER = NULL;
	WINDOW = NULL;

	TTF_Quit();
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
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

bool load_map_level_1(TILE* tiles[])
{
	if (!load_map_texture(map1_path_to_texture, RENDER))
	{
		cout << "Error with load map: fail to load map texture level 1 texture\n";
		return false;
	}
	else
	{
		if (!set_tile_map_level_1(tiles, map1_path_to_file))
		{
			cout << "Error with load map: fail to load map file level 1 texture\n";
			return false;
		}
	}
	return true;
}

void reload_game()
{
	main_Reaper.Reset_From_Start();
	main_Jungle_Pig.Reset_From_Start();
	open_gate_level_1(map1, gate_level_1);
}