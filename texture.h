#pragma once

#include <string>
#include <iostream>

using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

class TEXTURE
{
public:
	TEXTURE();
	~TEXTURE();

	bool load_texture_from_file(string path, SDL_Renderer* screen, bool use_set_color_key = false, Uint8 RED = 0, Uint8 GREEN = 0, Uint8 BLUE = 0);
	void render_texture_on_screen(int x, int y, SDL_Renderer* screen, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_texture_on_screen_type_2(int x, int y, SDL_Renderer* screen, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Set_Display_Width(const int& val) { mWidth = val; }
	void Set_Display_Height(const int& val) { mHeight = val; }

	void setBlend_mode(SDL_BlendMode blend) { SDL_SetTextureBlendMode(mTexture, blend); }
	void setAlpha(Uint8 alpha) { SDL_SetTextureAlphaMod(mTexture, alpha); }

	void free();
private:
	SDL_Texture* mTexture;
	int mWidth, mHeight;
};