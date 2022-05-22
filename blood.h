#pragma once
#include <string>
#include <vector>
#include <SDL.h>

#include "texture.h"

const int REAPER_TOTAL_BLOOD = 200;
const int JUNGLE_PIG_TOTAL_BLOOD = 1500;

class BLOOD
{
public:
	BLOOD();

	~BLOOD();

	bool Load_Blood_Texture(string path, SDL_Renderer* screen);

	void Render_Blood_Bar(SDL_Renderer* screen);


	void Set_Start_Blood(const int& val);

	void Set_Display_Blood(const int& val);

	void Set_Remain_Blood_Clip(const int& x, const int& y, const int& w, const int& h);

	void Set_Display_Blood_Bar_Clip(const int& x, const int& y, const int& w, const int& h);

	void Set_Remain_Blood_On_Screen(const int& x, const int& y, const int& w, const int& h);

	void Set_Display_Blood_Bar_On_Screen(const int& x, const int& y, const int& w, const int& h);


	void Reduce_Blood_By_Damage(const int& val);

	void Reset_Blood() { Current_Blood = Total_Blood; Display_Blood = save_display_blood; Remain_Blood_Texture.Set_Display_Width(Display_Blood); }

	int Get_Current_Blood()const { return Current_Blood; }
private:
	TEXTURE Display_Blood_Bar_Texture;
	TEXTURE Remain_Blood_Texture;
	TEXTURE Blood_Index;
	stringstream blood_text;

	SDL_Rect Remain_Blood_Clip;
	SDL_Rect Display_Blood_Bar;

	int Total_Blood;
	int save_display_blood;

	int Current_Blood, Display_Blood;
	int Blood_Render_Remain_Blood_Clip_x, Blood_Render_Remain_Blood_Clip_y;
	int Blood_Display_Blood_Bar_Clip_x, Blood_Display_Blood_Bar_Clip_y;
};


