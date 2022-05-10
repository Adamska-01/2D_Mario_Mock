#pragma once
#include <SDL_ttf.h>
#include "TextureManager.h"
#include <string>

class UI
{
private:
	TTF_Font* font{ nullptr };
	SDL_Texture* textTexture = { nullptr };
	
	SDL_Rect textRect;
	SDL_Color color;

public:
	UI(const char* p_path, int fontSize = 20);
	~UI();

	void Update(std::string p_text);
	void Render();

	void SetColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void SetPos(int p_x, int p_y, int p_w, int p_h);
};