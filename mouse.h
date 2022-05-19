#pragma once

#include "texture.h"

class MOUSE : public TEXTURE
{
public:
	MOUSE();
	~MOUSE();
	bool Load_Mouse_Texture(SDL_Renderer* screen);
	void Render_Mouse(SDL_Renderer* screen);
private:
	SDL_Rect mouse_rect;
};

static MOUSE mouse;