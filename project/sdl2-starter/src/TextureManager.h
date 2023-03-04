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
    map<string, SDL_Texture*> g_textureMap;
};

typedef TextureManager _TextureManager;