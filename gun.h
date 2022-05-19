#pragma once

#include "texture.h"
#include "Direction_Vector.h"

const int GUN_SIZE = 40;

class Gun : TEXTURE
{
public:
	Gun();
	~Gun();
	bool Load_Gun_Texture(SDL_Renderer* screen);
	void Update(SDL_Rect& camera);
	void Render_Gun(SDL_Renderer* screen);

	int Get_x() const { return gun_rect.x; }
	int Get_y() const { return gun_rect.y; }

	void set_rect(const int& x, const int& y) { gun_rect.x = x; gun_rect.y = y; }
private:
	SDL_Rect gun_rect;
	double Degree;
	SDL_RendererFlip Flip_Gun;
};
