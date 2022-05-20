#include "game_display.h"

MENU::MENU()
{
	request_a_reload = false;
	Screen_Status = START_SCREEN;
	change_music = false;
	turn_off_sound = false;

	Soundtrack_Playing = NULL;
	Soundtrack_Start_Game = NULL;
	Click_Button = NULL;
}

MENU::~MENU()
{
	start_play_button.free();
	quit_button.free();
	mini_menu_button.free();
	continue_button.free();
	back_to_start_button.free();
	yes_button.free();
	no_button.free();
}

bool MENU::Load_All_Button_And_Background_Display(SDL_Renderer* screen)
{

	// load menu button
	if (!start_play_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/play_button.png", true, 0, 0, 0))
	{
		cout << "fail to load button texture\n";
		return false;
	}
	else
	{
		start_play_button.Set_Display_Width(150);
		start_play_button.Set_Display_Height(40);
		start_play_button.set_button_rect(400, 475, 150, 40);
		start_play_button.set_button_clip_out(190, 57, 210, 75);
		start_play_button.set_button_clip_over(190, 257, 210, 75);
		start_play_button.set_button_clip_down(190, 457, 210, 75);
		start_play_button.set_button_clip_up(190, 257, 210, 75);
		start_play_button.set_in_use_button(true);
	}

	if (!quit_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/quit_button.png", true, 255, 255, 255))
	{
		cout << "fail to load button texture\n";
		return false;
	}
	else
	{
		quit_button.Set_Display_Width(40);
		quit_button.Set_Display_Height(40);
		quit_button.set_button_rect(SCREEN_WIDTH - 65, SCREEN_HEIGHT - 65, 40, 40);
		quit_button.set_button_clip_out(0, 0, 200, 200);
		quit_button.set_button_clip_over(0, 200, 200, 200);
		quit_button.set_button_clip_down(0, 400, 200, 200);
		quit_button.set_button_clip_up(0, 200, 200, 200);
		quit_button.set_in_use_button(true);
	}

	if (!mini_menu_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/menu_button.png", true, 255, 255, 255))
	{
		cout << "fail to load button texture\n";
		return false;
	}
	else
	{
		mini_menu_button.Set_Display_Width(60);
		mini_menu_button.Set_Display_Height(60);
		mini_menu_button.set_button_rect(SCREEN_WIDTH - 85, 25, 60, 60);
		mini_menu_button.set_button_clip_out(35, 35, 132, 132);
		mini_menu_button.set_button_clip_over(35, 234, 132, 132);
		mini_menu_button.set_button_clip_down(34, 434, 132, 132);
		mini_menu_button.set_button_clip_up(35, 234, 132, 132);
		mini_menu_button.set_in_use_button(false);
	}

	if (!continue_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/continue_button.png", true, 255, 255, 255))
	{
		cout << "fail to load button texture\n";
		return false;
	}
	else
	{
		continue_button.Set_Display_Width(350);
		continue_button.Set_Display_Height(70);
		continue_button.set_button_rect(450, (SCREEN_HEIGHT / 2 - 120), 350, 70);
		continue_button.set_button_clip_out(60, 50, 466, 90);
		continue_button.set_button_clip_over(60, 250, 466, 90);
		continue_button.set_button_clip_down(60, 450, 466, 90);
		continue_button.set_button_clip_up(60, 250, 466, 90);
		continue_button.set_in_use_button(false);
	}

	if (!back_to_start_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/back_button.png", true, 255, 255, 255))
	{
		cout << "fail to load button texture\n";
		return false;
	}
	else
	{
		back_to_start_button.Set_Display_Width(210);
		back_to_start_button.Set_Display_Height(70);
		back_to_start_button.set_button_rect(450, (SCREEN_HEIGHT / 2), 210, 70);
		back_to_start_button.set_button_clip_out(170, 45, 260, 95);
		back_to_start_button.set_button_clip_over(170, 245, 260, 95);
		back_to_start_button.set_button_clip_down(170, 445, 260, 95);
		back_to_start_button.set_button_clip_up(170, 245, 260, 95);
		back_to_start_button.set_in_use_button(false);
	}

	if (!yes_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/yes_button.png", true, 0, 0, 0))
	{
		cout << "error with load menu: fail to load yes button\n";
		return false;
	}
	else
	{
		yes_button.Set_Display_Width(150);
		yes_button.Set_Display_Height(75);
		yes_button.set_button_rect(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT - 200, 150, 75);
		yes_button.set_button_clip_out(210, 60, 162, 75);
		yes_button.set_button_clip_over(210, 260, 162, 75);
		yes_button.set_button_clip_down(210, 460, 162, 75);
		yes_button.set_button_clip_up(210, 260, 162, 75);
		yes_button.set_in_use_button(false);
	}

	if (!no_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/no_button.png", true, 0, 0, 0))
	{
		cout << "fail to load no button\n";
		return false;
	}
	else
	{
		no_button.Set_Display_Width(150);
		no_button.Set_Display_Height(75);
		no_button.set_button_rect(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT - 200, 150, 75);
		no_button.set_button_clip_out(245, 55, 124, 74);
		no_button.set_button_clip_over(245, 255, 124, 74);
		no_button.set_button_clip_down(245, 455, 124, 74);
		no_button.set_button_clip_up(245, 255, 124, 74);
		no_button.set_in_use_button(false);
	}

	if (!turn_on_off_sound_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/turn_on_off_sound_button.png", true, 255, 255, 255))
	{
		cout << "fail to load turn on off sound button\n";
		return false;
	}
	else
	{
		turn_on_off_sound_button.Set_Display_Width(40);
		turn_on_off_sound_button.Set_Display_Height(40);
		turn_on_off_sound_button.set_button_rect(SCREEN_WIDTH - 130, SCREEN_HEIGHT - 65, 40, 40);
		turn_on_off_sound_button.set_button_clip_out(15, 12, 166, 164);
		turn_on_off_sound_button.set_button_clip_over(15, 412, 166, 164);
		turn_on_off_sound_button.set_button_clip_down(15, 612, 166, 164);
		turn_on_off_sound_button.set_button_clip_up(15, 412, 166, 164);
		turn_on_off_sound_button.set_in_use_button(true);
	}

	if (!turn_on_help_screen_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/help_button.png", true, 255, 255, 255))
	{
		cout << "fail to load exit help screen button\n";
		return false;
	}
	else
	{
		turn_on_help_screen_button.Set_Display_Width(40);
		turn_on_help_screen_button.Set_Display_Height(40);
		turn_on_help_screen_button.set_button_rect(SCREEN_WIDTH - 195, SCREEN_HEIGHT - 65, 40, 40);
		turn_on_help_screen_button.set_button_clip_out(70, 55, 57, 80);
		turn_on_help_screen_button.set_button_clip_over(70, 255, 57, 80);
		turn_on_help_screen_button.set_button_clip_down(70, 455, 57, 80);
		turn_on_help_screen_button.set_button_clip_up(70, 255, 57, 80);
		turn_on_help_screen_button.set_in_use_button(true);
	}

	if (!exit_help_screen_button.load_button(screen, "GAME_TEXTURE/GAME_MENU_BUTTON/quit_button.png", true, 255, 255, 255))
	{
		cout << "fail to load exit help screen button\n";
		return false;
	}
	else
	{
		exit_help_screen_button.Set_Display_Width(40);
		exit_help_screen_button.Set_Display_Height(40);
		exit_help_screen_button.set_button_rect(SCREEN_WIDTH - 65, 25, 40, 40);
		exit_help_screen_button.set_button_clip_out(0, 0, 200, 200);
		exit_help_screen_button.set_button_clip_over(0, 200, 200, 200);
		exit_help_screen_button.set_button_clip_down(0, 400, 200, 200);
		exit_help_screen_button.set_button_clip_up(0, 200, 200, 200);
		exit_help_screen_button.set_in_use_button(false);
	}

	// load background

	if (!start_screen_background.load_texture_from_file("GAME_TEXTURE/BACKGROUND/start_screen.png", screen))
	{
		cout << "fail to load start screen background\n";
		return false;
	}
	if (!screen_after_lose_background.load_texture_from_file("GAME_TEXTURE/BACKGROUND/screen_after_lose.png", screen))
	{
		cout << "fail to load after lose background\n";
		return false;
	}
	if (!screen_after_win_background.load_texture_from_file("GAME_TEXTURE/BACKGROUND/screen_after_win.png", screen))
	{
		cout << "fail to load after win background\n";
		return false;
	}

	if (!help_screen_background.load_texture_from_file("GAME_TEXTURE/BACKGROUND/help_menu.png", screen))
	{
		cout << "fail to load help screen texture\n";
		return false;
	}

	if (!pause_screen_background.load_texture_from_file("GAME_TEXTURE/BACKGROUND/pause_screen.png", screen))
	{
		cout << "Error load background: fail to load pause screen background\n";
		return false;
	}

	return true;
}

bool MENU::load_sound_effect_and_music()
{
	Soundtrack_Start_Game = Mix_LoadMUS("SOUND_EFFECT_AND_MUSIC/start_game.wav");
	if (Soundtrack_Start_Game == NULL)
	{
		cout << "fail to load start game soundtrack\n";
		return false;
	}

	Soundtrack_Playing = Mix_LoadMUS("SOUND_EFFECT_AND_MUSIC/Forests.wav");
	if (Soundtrack_Playing == NULL)
	{
		cout << "fail to load start game soundtrack\n";
		return false;
	}

	Click_Button = Mix_LoadWAV("SOUND_EFFECT_AND_MUSIC/click.wav");
	if (Click_Button == NULL)
	{
		cout << "fail to load click button sound effect\n";
		return false;
	}

	return true;
}

void MENU::Handle_sound()
{
	if (turn_off_sound)
	{
		Mix_HaltMusic();
	}
	else
	{
		if (Screen_Status == START_SCREEN)
		{
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(Soundtrack_Start_Game, -1);
			}
			else if (Mix_PlayingMusic() && change_music)
			{
				Mix_HaltMusic();
				change_music = false;
			}
		}
		else if (Screen_Status == PLAY_SCREEN)
		{
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(Soundtrack_Playing, -1);
			}
			else if (Mix_PlayingMusic() && change_music)
			{
				Mix_HaltMusic();
				change_music = false;
			}
		}
	}

}

void MENU::Handle_All_Button(SDL_Event& e, bool& quit)
{
	start_play_button.handle_button(e);
	quit_button.handle_button(e);
	mini_menu_button.handle_button(e);
	continue_button.handle_button(e);
	back_to_start_button.handle_button(e);
	yes_button.handle_button(e);
	no_button.handle_button(e);
	turn_on_off_sound_button.handle_button(e);
	turn_on_help_screen_button.handle_button(e);
	exit_help_screen_button.handle_button(e);

	if (start_play_button.get_is_button_click())
	{
		start_play_button.set_is_button_click(false);
		Screen_Status = PLAY_SCREEN;
		request_a_reload = true;
		Set_PLaying_Screen();

		change_music = true;
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (quit_button.get_is_button_click())
	{
		Mix_PlayChannel(-1, Click_Button, 0);
		quit = true;
	}
	else if (mini_menu_button.get_is_button_click())
	{
		mini_menu_button.set_is_button_click(false);
		Screen_Status = PAUSE_SCREEN;
		Set_Pause_Screen();

		change_music = true;
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (continue_button.get_is_button_click())
	{
		continue_button.set_is_button_click(false);
		Screen_Status = PLAY_SCREEN;
		Set_PLaying_Screen();

		change_music = true;
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (back_to_start_button.get_is_button_click())
	{
		back_to_start_button.set_is_button_click(false);
		Screen_Status = START_SCREEN;
		request_a_reload = true;
		Set_Start_Screen();

		change_music = true;
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (yes_button.get_is_button_click())
	{
		yes_button.set_is_button_click(false);
		Screen_Status = PLAY_SCREEN;
		request_a_reload = true;
		Set_PLaying_Screen();

		change_music = true;
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (no_button.get_is_button_click())
	{
		no_button.set_is_button_click(false);
		Screen_Status = START_SCREEN;
		request_a_reload = true;
		Set_Start_Screen();

		change_music = true;
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (turn_on_off_sound_button.get_is_button_click())
	{
		turn_on_off_sound_button.set_is_button_click(false);


		if (turn_off_sound == true)
		{
			turn_off_sound = false;
			turn_on_off_sound_button.set_button_clip_out(15, 12, 166, 164);
			turn_on_off_sound_button.set_button_clip_over(15, 412, 166, 164);
			turn_on_off_sound_button.set_button_clip_down(15, 612, 166, 164);
			turn_on_off_sound_button.set_button_clip_up(15, 412, 166, 164);
		}
		else if (turn_off_sound == false)
		{
			turn_off_sound = true;
			turn_on_off_sound_button.set_button_clip_out(15, 612, 166, 164);
			turn_on_off_sound_button.set_button_clip_over(15, 812, 166, 164);
			turn_on_off_sound_button.set_button_clip_down(15, 1012, 166, 164);
			turn_on_off_sound_button.set_button_clip_up(15, 812, 166, 164);
		}
		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (turn_on_help_screen_button.get_is_button_click())
	{
		turn_on_help_screen_button.set_is_button_click(false);
		Screen_Status = HELP_SCREEN;
		Set_Help_Screen();

		Mix_PlayChannel(-1, Click_Button, 0);
	}
	else if (exit_help_screen_button.get_is_button_click())
	{
		exit_help_screen_button.set_is_button_click(false);
		Screen_Status = START_SCREEN;
		Set_Start_Screen();

		Mix_PlayChannel(-1, Click_Button, 0);
	}
}

void MENU::Render_Menu_Button(SDL_Renderer* screen)
{
	start_play_button.render_button(screen);
	quit_button.render_button(screen);
	mini_menu_button.render_button(screen);
	continue_button.render_button(screen);
	back_to_start_button.render_button(screen);
	yes_button.render_button(screen);
	no_button.render_button(screen);
	turn_on_off_sound_button.render_button(screen);
	turn_on_help_screen_button.render_button(screen);
	exit_help_screen_button.render_button(screen);
}

void MENU::Render_Background(SDL_Renderer* screen)
{
	if (Screen_Status == START_SCREEN)
	{
		start_screen_background.render_texture_on_screen(0, 0, screen);
	}
	else if (Screen_Status == SCREEN_AFTER_LOSE)
	{
		screen_after_lose_background.render_texture_on_screen(0, 0, screen);
	}
	else if (Screen_Status == SCREEN_AFTER_WIN)
	{
		screen_after_win_background.render_texture_on_screen(0, 0, screen);
	}
	else if (Screen_Status == HELP_SCREEN)
	{
		help_screen_background.render_texture_on_screen(0, 0, screen);
	}
	else if (Screen_Status == PAUSE_SCREEN)
	{
		pause_screen_background.render_texture_on_screen(0, 0, screen);
	}
	else return;
}

void MENU::Set_Start_Screen()
{
	start_play_button.set_in_use_button(true);
	quit_button.set_in_use_button(true);
	turn_on_off_sound_button.set_in_use_button(true);
	mini_menu_button.set_in_use_button(false);
	continue_button.set_in_use_button(false);
	back_to_start_button.set_in_use_button(false);
	yes_button.set_in_use_button(false);
	no_button.set_in_use_button(false);
	turn_on_help_screen_button.set_in_use_button(true);
	exit_help_screen_button.set_in_use_button(false);
}

void MENU::Set_PLaying_Screen()
{
	start_play_button.set_in_use_button(false);
	quit_button.set_in_use_button(false);
	turn_on_off_sound_button.set_in_use_button(false);
	mini_menu_button.set_in_use_button(true);
	continue_button.set_in_use_button(false);
	back_to_start_button.set_in_use_button(false);
	yes_button.set_in_use_button(false);
	no_button.set_in_use_button(false);
	turn_on_help_screen_button.set_in_use_button(false);
	exit_help_screen_button.set_in_use_button(false);
}

void MENU::Set_Pause_Screen()
{
	start_play_button.set_in_use_button(false);
	quit_button.set_in_use_button(false);
	turn_on_off_sound_button.set_in_use_button(true);
	mini_menu_button.set_in_use_button(false);
	continue_button.set_in_use_button(true);
	back_to_start_button.set_in_use_button(true);
	yes_button.set_in_use_button(false);
	no_button.set_in_use_button(false);
	turn_on_help_screen_button.set_in_use_button(false);
	exit_help_screen_button.set_in_use_button(false);
}

void MENU::Set_Screen_After_Lose()
{
	start_play_button.set_in_use_button(false);
	quit_button.set_in_use_button(false);
	turn_on_off_sound_button.set_in_use_button(false);
	mini_menu_button.set_in_use_button(false);
	continue_button.set_in_use_button(false);
	back_to_start_button.set_in_use_button(false);
	yes_button.set_in_use_button(true);
	no_button.set_in_use_button(true);
	turn_on_help_screen_button.set_in_use_button(false);
	exit_help_screen_button.set_in_use_button(false);
}

void MENU::Set_Screen_After_Win()
{
	start_play_button.set_in_use_button(false);
	quit_button.set_in_use_button(false);
	turn_on_off_sound_button.set_in_use_button(false);
	mini_menu_button.set_in_use_button(false);
	continue_button.set_in_use_button(false);
	back_to_start_button.set_in_use_button(false);
	yes_button.set_in_use_button(true);
	no_button.set_in_use_button(true);
	turn_on_help_screen_button.set_in_use_button(false);
	exit_help_screen_button.set_in_use_button(false);
}

void MENU::Set_Help_Screen()
{
	start_play_button.set_in_use_button(false);
	quit_button.set_in_use_button(false);
	turn_on_off_sound_button.set_in_use_button(false);
	mini_menu_button.set_in_use_button(false);
	continue_button.set_in_use_button(false);
	back_to_start_button.set_in_use_button(false);
	yes_button.set_in_use_button(false);
	no_button.set_in_use_button(false);
	turn_on_help_screen_button.set_in_use_button(false);
	exit_help_screen_button.set_in_use_button(true);
}