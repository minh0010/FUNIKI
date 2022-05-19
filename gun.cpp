#include "gun.h"

Gun::Gun()
{
	gun_rect = { 0,0,0,0 };
	Degree = 0.0;
	Flip_Gun = SDL_FLIP_NONE;
}

Gun::~Gun()
{
	free();
}

bool Gun::Load_Gun_Texture(SDL_Renderer* screen)
{
	if (!TEXTURE::load_texture_from_file("GAME_TEXTURE/WEAPON/gun.png", screen, true, 255, 255, 255))
	{
		return false;
	}
	else
	{
		TEXTURE::Set_Display_Width(GUN_SIZE);
		TEXTURE::Set_Display_Height(GUN_SIZE);
	}
	return true;
}

void Gun::Update(SDL_Rect& camera)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	Direction_Vector from_gun_to_mouse = Direction_Vector(float(x - gun_rect.x), float(y - gun_rect.y));
	Direction_Vector unit_vector = Direction_Vector(1.0f, 0.0f);

	float cos_val = Cosin_Value_Between_Two_Vector(from_gun_to_mouse, unit_vector);

	Degree = (double)acos(cos_val) * 180 / M_PI;

	if (y < gun_rect.y) Degree = 360.0 - Degree;

	if (x < gun_rect.x) Flip_Gun = SDL_FLIP_VERTICAL;
	else if (x > gun_rect.x) Flip_Gun = SDL_FLIP_NONE;
}

void Gun::Render_Gun(SDL_Renderer* screen)
{
	TEXTURE::render_texture_on_screen(gun_rect.x, gun_rect.y, screen, NULL, Degree, NULL, Flip_Gun);
}