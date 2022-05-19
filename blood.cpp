#include "blood.h"

BLOOD::BLOOD()
{
	Remain_Blood_Clip = { 0,0,0,0 };
	Display_Blood_Bar = { 0,0,0,0 };

	Total_Blood = 0;
	save_display_blood = 0;

	Current_Blood = 0;
	Display_Blood = 0;

	Blood_Render_Remain_Blood_Clip_x = 0;
	Blood_Render_Remain_Blood_Clip_y = 0;
	Blood_Display_Blood_Bar_Clip_x = 0;
	Blood_Display_Blood_Bar_Clip_y = 0;
}

BLOOD::~BLOOD()
{
	Display_Blood_Bar_Texture.free();
	Remain_Blood_Texture.free();
}

bool BLOOD::Load_Blood_Texture(string path, SDL_Renderer* screen)
{
	if (!Display_Blood_Bar_Texture.load_texture_from_file(path, screen, true, 0, 125, 180))
	{
		cout << "fail to load display blood bar\n";
		return false;
	}
	if (!Remain_Blood_Texture.load_texture_from_file(path, screen, true, 0, 125, 180))
	{
		cout << "fail to load display blood bar\n";
		return false;
	}
	return true;
}

void BLOOD::Render_Blood_Bar(SDL_Renderer* screen)
{
	Display_Blood_Bar_Texture.render_texture_on_screen(Blood_Display_Blood_Bar_Clip_x, Blood_Display_Blood_Bar_Clip_y, screen, &Display_Blood_Bar);
	Remain_Blood_Texture.render_texture_on_screen(Blood_Render_Remain_Blood_Clip_x, Blood_Render_Remain_Blood_Clip_y, screen, &Remain_Blood_Clip);
}

void BLOOD::Set_Start_Blood(const int& val)
{
	Total_Blood = val;
	Current_Blood = val;
}

void BLOOD::Set_Display_Blood(const int& val)
{
	Display_Blood = val;
	save_display_blood = val;
}

void BLOOD::Set_Remain_Blood_Clip(const int& x, const int& y, const int& w, const int& h)
{
	Remain_Blood_Clip.x = x;
	Remain_Blood_Clip.y = y;
	Remain_Blood_Clip.w = w;
	Remain_Blood_Clip.h = h;
}

void BLOOD::Set_Display_Blood_Bar_Clip(const int& x, const int& y, const int& w, const int& h)
{
	Display_Blood_Bar.x = x;
	Display_Blood_Bar.y = y;
	Display_Blood_Bar.w = w;
	Display_Blood_Bar.h = h;
}

void BLOOD::Set_Remain_Blood_On_Screen(const int& x, const int& y, const int& w, const int& h)
{
	Blood_Render_Remain_Blood_Clip_x = x;
	Blood_Render_Remain_Blood_Clip_y = y;
	Remain_Blood_Texture.Set_Display_Width(w);
	Remain_Blood_Texture.Set_Display_Height(h);
}

void BLOOD::Set_Display_Blood_Bar_On_Screen(const int& x, const int& y, const int& w, const int& h)
{

	Blood_Display_Blood_Bar_Clip_x = x;
	Blood_Display_Blood_Bar_Clip_y = y;
	Display_Blood_Bar_Texture.Set_Display_Width(w);
	Display_Blood_Bar_Texture.Set_Display_Height(h);
}

void BLOOD::Reduce_Blood_By_Damage(const int& val)
{
	double Blood_After_Get_Damage = (double)Current_Blood - val;
	if (Blood_After_Get_Damage >= 0)
	{
		double Display_Blood_After_Get_Damage = (Blood_After_Get_Damage * Display_Blood) / Current_Blood;

		if (Display_Blood_After_Get_Damage <= 0.0) Display_Blood_After_Get_Damage = 0.0;


		Current_Blood -= val;
		Display_Blood = (int)Display_Blood_After_Get_Damage;
		Remain_Blood_Texture.Set_Display_Width(Display_Blood);
	}
	else
	{
		Current_Blood = 0;
		Display_Blood = 0;
		Remain_Blood_Texture.Set_Display_Width(0);
	}
}