#include "UI.h"
#include <iostream>

UI::UI(const char* p_path, int fontSize)
{
	//init ttf
	if (TTF_Init() < 0)
		std::cout << "Error: " << TTF_GetError() << std::endl;
	else
		font = TTF_OpenFont(p_path, fontSize);
}

UI::~UI()
{
	if (font != nullptr)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
	if (textTexture != nullptr)
	{
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}
}

void UI::Update(std::string p_text)
{
	textTexture = TextureManager::LoadText(font, p_text.c_str(), color);
}

void UI::Render()
{
	SDL_RenderCopy(Game::renderer, textTexture, NULL, &textRect);
}

void UI::SetColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	color.r = p_r;
	color.g = p_g;
	color.b = p_b;
	color.a = p_a;
}

void UI::SetPos(int p_x, int p_y, int p_w, int p_h)
{
	textRect.x = p_x;
	textRect.y = p_y;
	textRect.w = p_w;
	textRect.h = p_h;
}
