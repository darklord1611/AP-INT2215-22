
#ifndef __GameObject__
#define __GameObject__

#include "LoaderParams.h"
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<map>
#include<iostream>

using namespace std;

class GameObject 
{
protected:
    GameObject() {}
    virtual ~GameObject() {}
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    virtual void load(const LoaderParams* pParams) = 0;  
};

#endif // define __GameObject__
