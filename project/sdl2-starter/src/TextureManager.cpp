#include "TextureManager.h"

TextureManager* TextureManager::instance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer* g_renderer) 
{
    SDL_Surface* g_temp_surface = IMG_Load(fileName.c_str());

    if(g_temp_surface == 0) 
    {
        cout << SDL_GetError() << endl;
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

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* g_renderer, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
    
    SDL_SetTextureAlphaMod(g_textureMap[id], alpha);
	SDL_RenderCopyEx(g_renderer, g_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::clearFromTextureMap(string id) 
{
    g_textureMap.erase(id);
}

void TextureManager::clearTextureMap() 
{
    g_textureMap.clear();
}

/*bool TextureManager::loadFont(string message, string id, SDL_Renderer* g_renderer) 
{
    if (TTF_Init() < 0) 
    {
        cerr << "SDL_ttf could not initialize: " << TTF_GetError() << endl;
        return false;
    }
    // Load the font
    TTF_Font* font = TTF_OpenFont("assets/arial.ttf", 24);
    if (font == nullptr) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
        return false;
    }
    SDL_Color textColor = { 255, 0, 0, 255 }; 
    SDL_Surface* g_temp_surface = TTF_RenderText_Solid(font, message.c_str(), textColor);

    if(g_temp_surface == 0) 
    {
        cout << SDL_GetError() << endl;
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
}*/