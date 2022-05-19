#include "button.h"

BUTTON::BUTTON()
{
	button_rect = { 0,0,0,0 };
	for (int i = 0; i < total_button_clip; ++i) button_clip[i] = { 0,0,0,0 };
	status = mouse_out;
	in_use_button = false;
	is_button_click = false;
}

BUTTON::~BUTTON()
{
}

bool BUTTON::load_button(SDL_Renderer* screen, string path, bool use_set_color_key, Uint8 RED, Uint8 GREEN, Uint8 BLUE)
{
	bool load = TEXTURE::load_texture_from_file(path, screen, use_set_color_key, RED, GREEN, BLUE);
	return load;
}

void BUTTON::handle_button(SDL_Event& e)
{
	if ((e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) && in_use_button)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if (x < button_rect.x) inside = false;
		if (x > button_rect.x + button_rect.w) inside = false;
		if (y < button_rect.y) inside = false;
		if (y > button_rect.y + button_rect.h) inside = false;

		if (inside)
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				status = mouse_over;
				break;
			case SDL_MOUSEBUTTONUP:
				is_button_click = true;
				status = mouse_up;
				break;
			case SDL_MOUSEBUTTONDOWN:
				status = mouse_down;
				break;
			}
		}
		else status = mouse_out;
	}
	else return;
}

void BUTTON::render_button(SDL_Renderer* screen)
{
	if (in_use_button) TEXTURE::render_texture_on_screen(button_rect.x, button_rect.y, screen, &button_clip[status]);
}