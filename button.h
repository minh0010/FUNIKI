#pragma once

#include "texture.h"

class BUTTON : public TEXTURE
{
public:
	const int total_button_clip = 4; 


	enum mouse_status
	{
		mouse_out = 0,
		mouse_over = 1,
		mouse_down = 2,
		mouse_up = 3
	};

	BUTTON();

	~BUTTON();

	void set_in_use_button(const bool& val) { in_use_button = val; }

	void set_is_button_click(const bool& val) { is_button_click = val; }

	void set_button_rect(const int& x, const int& y, const int& w, const int& h)
	{
		button_rect.x = x; button_rect.y = y; button_rect.h = h; button_rect.w = w;
	}

	void set_button_clip_out(const int& x, const int& y, const int& w, const int& h)
	{
		button_clip[mouse_out].x = x;
		button_clip[mouse_out].y = y;
		button_clip[mouse_out].w = w;
		button_clip[mouse_out].h = h;
	}
	void set_button_clip_over(const int& x, const int& y, const int& w, const int& h)
	{
		button_clip[mouse_over].x = x;
		button_clip[mouse_over].y = y;
		button_clip[mouse_over].w = w;
		button_clip[mouse_over].h = h;
	}
	void set_button_clip_down(const int& x, const int& y, const int& w, const int& h)
	{
		button_clip[mouse_down].x = x;
		button_clip[mouse_down].y = y;
		button_clip[mouse_down].w = w;
		button_clip[mouse_down].h = h;
	}
	void set_button_clip_up(const int& x, const int& y, const int& w, const int& h)
	{
		button_clip[mouse_up].x = x;
		button_clip[mouse_up].y = y;
		button_clip[mouse_up].w = w;
		button_clip[mouse_up].h = h;
	}



	bool load_button(SDL_Renderer* screen, string path, bool use_set_color_key = false, Uint8 RED = 0, Uint8 GREEN = 0, Uint8 BLUE = 0);
	void handle_button(SDL_Event& e);
	void render_button(SDL_Renderer* screen);


	bool get_is_button_click() const { return is_button_click; }
	bool get_is_button_in_use() const { return in_use_button; }
private:
	SDL_Rect button_rect;
	SDL_Rect button_clip[4];
	int status;
	bool in_use_button;
	bool is_button_click;
};

