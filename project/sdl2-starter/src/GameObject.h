#pragma once
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<map>
#include<iostream>

using namespace std;

class GameObject { 
public:
    virtual void load(int x, int y, int width, int height, string textureID, string fileName);
    virtual void draw(SDL_Renderer* g_renderer);
    virtual void update();
    virtual void clean() {};  
protected:
    string m_fileName;
    string m_textureID;
    int m_x; 
    int m_y;
    int m_width;
    int m_height; 
};