#include "TextureManager.h"

TextureManager* TextureManager::instance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer* g_renderer) 
{
    SDL_Surface* g_temp_surface = IMG_Load(fileName.c_str());

    if(g_temp_surface == 0) 
    {
        cout << SDL_GetError();
        return false;
    }
    SDL_Texture* g_texture = SDL_CreateTextureFromSurface(g_renderer, g_temp_surface);
    SDL_FreeSurface(g_temp_surface);
    if(g_texture == NULL) 
    {
        cout << SDL_GetError() << endl;
        return false;
    }
    g_textureMap[id] = g_texture;
    return true;
}

void TextureManager::draw(string id, int x, int y, int width, int height, SDL_Renderer* g_renderer, SDL_RendererFlip flip) 
{
    SDL_Rect srcRect; SDL_Rect destRect;
    srcRect.x = 0; 
    srcRect.y = 0; 
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height; 
    destRect.x = x; 
    destRect.y = y;
    SDL_RenderCopyEx(g_renderer, g_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* g_renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(g_renderer, g_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

// draw tiles with margin and spacing
void TextureManager::drawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* g_renderer) 
{
    SDL_Rect srcRect, desRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentFrame;
    srcRect.w = width;
    srcRect.h = height;
    desRect.w = width;
    desRect.h = height;
    desRect.x = x;
    desRect.y = y;
    SDL_RenderCopyEx(g_renderer, m_textureMap[id], &srcRect, &desRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearFromTextureMap(string id) 
{
    g_textureMap.erase(id);
}