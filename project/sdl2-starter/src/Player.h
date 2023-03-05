#include "GameObject.h"


class Player: public GameObject 
{
public:
    void load(int x, int y, int width, int height, string textureID, string fileName); 
    void draw(SDL_Renderer* g_renderer); 
    void update(); 
    void clean();
};