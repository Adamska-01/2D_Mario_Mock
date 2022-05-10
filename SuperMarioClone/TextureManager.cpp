#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    SDL_FreeSurface(tempSurface);
    tempSurface = nullptr;

    return texture;
}

SDL_Texture* TextureManager::LoadText(TTF_Font* p_font, const char* p_string, SDL_Color p_color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(p_font, p_string, p_color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(Game::renderer, textSurface);

    SDL_FreeSurface(textSurface);
    textSurface = nullptr;

    return text;
}

void TextureManager::Draw(SDL_Texture* p_Texture, SDL_Rect p_src, SDL_Rect p_dest)
{
    SDL_RenderCopy(Game::renderer, p_Texture, &p_src, &p_dest);
}
