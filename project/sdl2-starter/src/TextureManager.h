#ifndef __TextureManager__
#define __TextureManager__

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<map>
#include<iostream>
#include<string>

using namespace std;

class TextureManager 
{
private:
    static TextureManager* instance;
    TextureManager() {}
    ~TextureManager() {}
public:
    static TextureManager* Instance() 
        {
            if(instance == 0) 
            {
                instance = new TextureManager();
            }
            return instance;
        }
        
    bool load(string fileName, string id, SDL_Renderer* g_renderer);
    void draw(string id, int x, int y, int width, int height, SDL_Renderer* g_renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* g_renderer, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);
    map<string, SDL_Texture*> g_textureMap;
    void clearFromTextureMap(string id);
    void clearTextureMap();
    map<string, SDL_Texture*> getTextureMap() { return g_textureMap; }
};
typedef TextureManager _TextureManager;

#endif // define __TextureManager__