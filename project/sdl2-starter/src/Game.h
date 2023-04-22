#ifndef __Game__
#define __Game__


#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
#include "GameStateMachine.h"

using namespace std;

class Game
{
private:
    Game();
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
    bool m_continue;
    int m_currentLevel;
    bool m_levelComplete;

    vector<string> m_levelFiles;
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

    // setter and getter
    int getGameHeight() const { return m_gameHeight; }
    int getGameWidth() const { return m_gameWidth; }
    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }
    int getScore() { return m_Score; }
    void setScore(int score);
    void setCurrentLevel(int currentLevel);
    int getCurrentLevel() { return m_currentLevel; }
    void setLevelComplete(bool completed) { m_levelComplete = completed; }
    bool getLevelComplete() { return m_levelComplete; }
    vector<string> getLevelFiles() { return m_levelFiles; } 

    // score
    void upgradeCurrentScore(int score);
    void loadHighScore();
    void compareScore();
    double getScrollSpeed() { return m_scrollSpeed; }
    bool resumeGame() { return m_continue; }
};
typedef Game theGame;

#endif /* defined(__Game__) */
