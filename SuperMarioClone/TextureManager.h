#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadText(TTF_Font* p_font, const char* p_string, SDL_Color p_color);
	static void Draw(SDL_Texture* p_Texture, SDL_Rect p_src, SDL_Rect p_dest);
};