#include "texture.h"


TEXTURE::TEXTURE()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

TEXTURE::~TEXTURE()
{
	free();
}

bool TEXTURE::load_texture_from_file(string path, SDL_Renderer* screen, bool use_set_color_key, Uint8 RED, Uint8 GREEN, Uint8 BLUE)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL)
	{
		cout << "can not load surface from file\n";
		return false;
	}
	else
	{
		if (use_set_color_key)
		{
			SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, RED, GREEN, BLUE));
		}
		newTexture = SDL_CreateTextureFromSurface(screen, loaded_surface);
		if (newTexture == NULL)
		{
			cout << "can not create texture from surface\n";
			return false;
		}
		else
		{
			mWidth = loaded_surface->w;
			mHeight = loaded_surface->h;

			SDL_FreeSurface(loaded_surface);
			loaded_surface = NULL;
		}
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void TEXTURE::render_texture_on_screen(int x, int y, SDL_Renderer* screen, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect render_quad = { x,y,mWidth,mHeight };
	SDL_RenderCopyEx(screen, mTexture, clip, &render_quad, angle, center, flip);
}

void TEXTURE::render_texture_on_screen_type_2(int x, int y, SDL_Renderer* screen, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect render_quad = { x,y,mWidth,mHeight };
	if (clip != NULL)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, mTexture, clip, &render_quad, angle, center, flip);
}

void TEXTURE::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}