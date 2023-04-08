#ifndef __Game__
#define __Game__
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include "Player.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "AnimatedGraphic.h"
#include "GameObjectFactory.h"
#include "MainMenuState.h"
#include "Glider.h"
#include "BulletHandler.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Turret.h"
#include "RoofTurret.h"
#include "ScrollingBackground.h"

using namespace std;

class Game
{
private:
    Game() {}
    ~Game();
    int m_playerLives;
    int m_Score;
    static Game* instance;
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    bool isRunning;
    GameStateMachine* g_gameStateMachine;
    int m_gameHeight;
    double m_scrollSpeed;
    int m_gameWidth;
public:
    static Game* Instance() 
        {
            if(instance == 0) 
            {
                instance = new Game();
            }
            return instance;
        }
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags); 
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit();
    bool running() { return isRunning; }
    SDL_Renderer* getRenderer() { return g_renderer; }
    GameStateMachine* getStateMachine() { return g_gameStateMachine; }
    int getGameHeight() const { return m_gameHeight; }
    int getGameWidth() const { return m_gameWidth; }
    void setPlayerLives(int lives) { m_playerLives = lives; }
    //void setScore(int score) { m_Score = score; }
    int getScore() { return m_Score; }
    int getPlayerLives() { return m_playerLives; }
    double getScrollSpeed() { return m_scrollSpeed; }
};
typedef Game theGame;

#endif /* defined(__Game__) */
