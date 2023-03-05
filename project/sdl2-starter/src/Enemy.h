#include "GameObject.h"


class Enemy : public GameObject 
{
    public:
        void load(int x, int y, int width, int height, string textureID, string fileName); 
        void draw(SDL_Renderer* g_renderer); 
        void update(); 
        void clean() {};
};