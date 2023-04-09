#include "Game.h"
#include "MainMenuState.h"
// inputs
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "InputHandler.h"
// objects
#include "ScrollingBackground.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "Player.h"
#include "Glider.h"
#include "Turret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "RoofTurret.h"
#include "Boss.h"

// utility
#include<cstdlib>
#include<fstream>


Game* Game::instance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
    m_scrollSpeed = 0.8;
    m_Score = 0;
    m_gameHeight = height;
    m_gameWidth = width;
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) 
    {
        cout << "SDL_Init failed with error: " << SDL_GetError() << endl;
        return false;
    }
    g_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(g_window != 0) 
    {
        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_PRESENTVSYNC);
        if(g_renderer != 0) 
        {
            SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
        }
    }
    // music
    TheSoundManager::Instance()->load("assets/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
    TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
    TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);
    TheSoundManager::Instance()->playMusic("music1", -1);
    // register type

    _GameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
    _GameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    _GameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    _GameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    _GameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
    _GameObjectFactory::Instance()->registerType("Boss", new BossCreator());
    _GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    _GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    _GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    _GameObjectFactory::Instance()->registerType("Background", new ScrollingBackgroundCreator());

    g_gameStateMachine = new GameStateMachine();
	g_gameStateMachine->pushState(new MainMenuState());
    return true;
}


void Game::render() 
{
    SDL_RenderClear(g_renderer);
    g_gameStateMachine->render();

    SDL_RenderPresent(g_renderer);
}

void Game::update() 
{
    g_gameStateMachine->update();
}

void Game::clean()
{
    cout << "cleaning game\n";
    _InputHandler::Instance()->clean();
    // g_gameStateMachine->clean();
    // g_gameStateMachine = 0;
    // delete g_gameStateMachine;
    _TextureManager::Instance()->clearTextureMap();
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();
}

void Game::handleEvents() 
{
    _InputHandler::Instance()->update(); 
}

void Game::quit() 
{
    isRunning = false;
}

Game::~Game()
{
    g_renderer = 0;
    g_window = 0;
}


void Game::loadHighScore() 
{
    string fileName = "assets/highscore.txt";
    int value;
    ifstream file(fileName.c_str());
    if(file) 
    {
        file >> value;
        file.close();
    } else 
    {
        cout << "cant open file" << endl;
        return;
    }
    _TextureManager::Instance()->clearFromTextureMap("highscore");
    if(!_TextureManager::Instance()->loadFont(to_string(value), "highscore", g_renderer, {255, 0, 0})) 
    {
        cout << "something wrong" << endl;
        return;
    }
}

void Game::upgradeCurrentScore(int score) 
{
    m_Score += score;
    _TextureManager::Instance()->clearFromTextureMap("current_score");
    _TextureManager::Instance()->loadFont(to_string(m_Score), "current_score", g_renderer);
}

void Game::compareScore() 
{
    string fileName = "assets/highscore.txt";
    int highScore;
    ifstream file(fileName.c_str());
    if(file) 
    {
        file >> highScore;
        file.close();
    } else 
    {
        cout << "cant open file" << endl;
        return;
    }
    if(m_Score > highScore) 
    {
        ofstream file(fileName.c_str());
        if(file) 
        {
            file << m_Score;
            file.close();
        } else 
        {
            cout << "cant open file" << endl;
            return;
        }
    }
}
