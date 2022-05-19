#pragma once

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

static TTF_Font* GAME_FONT = NULL;
static SDL_Color FONT_COLOR = { 255,255,255,255 };
bool Load_Game_Font();


class TEXTURE
{
public:
	TEXTURE();
	~TEXTURE();

	// create texture from picture
	bool load_texture_from_file(string path, SDL_Renderer* screen, bool use_set_color_key = false, Uint8 RED = 0, Uint8 GREEN = 0, Uint8 BLUE = 0);
	
	#if defined(SDL_TTF_MAJOR_VERSION)
	// create texture from font string
	bool loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* screen);
	#endif

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