#pragma once

#include <SDL_mixer.h>

#include "button.h"
#include "mouse.h"

// total menu

enum STATUS
{
	START_SCREEN = 10,
	PLAY_SCREEN = 20,
	PAUSE_SCREEN = 30,
	SCREEN_AFTER_LOSE = 40,
	SCREEN_AFTER_WIN = 50,
	HELP_SCREEN = 60
};

class MENU
{
public:


	MENU();
	~MENU();

	bool Load_All_Button_And_Background_Display(SDL_Renderer* screen);

	bool load_sound_effect_and_music();



	void Handle_All_Button(SDL_Event& e, bool& quit);

	void Handle_sound();

	void Render_Menu_Button(SDL_Renderer* screen);

	void Render_Background(SDL_Renderer* screen);



	void Set_Start_Screen();

	void Set_PLaying_Screen();

	void Set_Pause_Screen();

	void Set_Screen_After_Lose();

	void Set_Screen_After_Win();

	void Set_Help_Screen();

	void Set_Screen_Status(const int& val) { Screen_Status = val; }

	void Set_Request_A_Reload(const bool& val) { request_a_reload = val; }


	bool Get_Request_A_Reload() const { return request_a_reload; }

	int Get_Screen_Status() const { return Screen_Status; }
private:

	// control menu button
	BUTTON start_play_button;
	BUTTON quit_button;
	BUTTON mini_menu_button;
	BUTTON continue_button;
	BUTTON back_to_start_button;
	BUTTON yes_button;
	BUTTON no_button;
	BUTTON turn_on_off_sound_button;
	BUTTON turn_on_help_screen_button;
	BUTTON exit_help_screen_button;

	// bacl ground display base on current screen

	TEXTURE start_screen_background;
	TEXTURE screen_after_lose_background;
	TEXTURE screen_after_win_background;
	TEXTURE help_screen_background;
	TEXTURE pause_screen_background;

	// sound effect and music

	Mix_Music* Soundtrack_Start_Game;
	Mix_Music* Soundtrack_Playing;
	Mix_Chunk* Click_Button;

	bool request_a_reload;
	int Screen_Status;
	bool change_music;
	bool turn_off_sound;
};

static MENU FUNIKI_MENU;