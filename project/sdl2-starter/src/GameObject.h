#include "LoaderParams.h"
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<map>
#include<iostream>

using namespace std;

class GameObject 
{
protected:
    GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;  
};
