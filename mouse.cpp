#include "mouse.h"

MOUSE::MOUSE()
{
	mouse_rect = { 0,0,0,0 };
	SDL_ShowCursor(false);
}

MOUSE::~MOUSE()
{
	free();
}

bool MOUSE::Load_Mouse_Texture(SDL_Renderer* screen)
{
	if (!TEXTURE::load_texture_from_file("GAME_TEXTURE/GAME_MOUSE/mouse.png", screen, true, 255, 255, 255))
	{
		cout << "fail to load mouse texture\n";
		return false;
	}
	else
	{
		TEXTURE::Set_Display_Width(30);
		TEXTURE::Set_Display_Height(30);
		mouse_rect = { 18,17,111,94 };
		SDL_ShowCursor(false);
	}

	return true;
}

void MOUSE::Render_Mouse(SDL_Renderer* screen)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	TEXTURE::render_texture_on_screen(x, y, screen, &mouse_rect);
}