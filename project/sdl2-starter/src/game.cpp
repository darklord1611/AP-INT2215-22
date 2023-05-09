#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
// inputs
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
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
#include "SmallEskeletor.h"
// utility
#include<cstdlib>
#include "Utility.h"

const int score_size = 12;

Game* Game::instance = 0;

Game::Game() 
{
    m_continue = false;
    m_scrollSpeed = 0.8;
    m_Score = 0;
    g_window = 0;
    g_renderer = 0;
    m_playerLives = 3;
    isRunning = false;
    m_levelFiles.push_back("assets/level1.xml");
    m_levelFiles.push_back("assets/level2.xml");
    m_levelFiles.push_back("assets/level3.xml");
    m_levelFiles.push_back("assets/level1.xml");
    m_levelFiles.push_back("assets/level2.xml");
    m_levelFiles.push_back("assets/level3.xml");
    m_levelFiles.push_back("assets/level1.xml");
    m_levelFiles.push_back("assets/level2.xml");
    m_levelFiles.push_back("assets/level3.xml");
    m_levelFiles.push_back("assets/levelBoss.xml");
    m_currentLevel = 1;
    upgradeCurrentScore(m_Score);
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
    m_continue = false;
    m_scrollSpeed = 0.2;
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
    _GameObjectFactory::Instance()->registerType("SmallEskeletor", new SmallEskeletorCreator());
    
    // initialize
    g_gameStateMachine = new GameStateMachine();
    TiXmlDocument doc;
    if(!doc.LoadFile("assets/pause.xml")) 
    {
        g_gameStateMachine->pushState(new MainMenuState());
    }
	else 
    {
        m_continue = true;
        g_gameStateMachine->pushState(new PlayState());
        g_gameStateMachine->pushState(new PauseState());
    }
    isRunning = true;
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
    g_gameStateMachine->clean();
    // g_gameStateMachine = 0;
    delete g_gameStateMachine;
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
    int high_score = getHighScore("assets/highscore.txt");
    _TextureManager::Instance()->clearFromTextureMap("highscore");
    _TextureManager::Instance()->loadFont(modify(high_score), "highscore", g_renderer, score_size, {255, 0, 0});
}

void Game::upgradeCurrentScore(int score) 
{
    m_Score += score;
    _TextureManager::Instance()->clearFromTextureMap("current_score");
    _TextureManager::Instance()->loadFont(modify(m_Score), "current_score", g_renderer);
}

void Game::compareScore() 
{
    replaceHighScore(m_Score, "assets/highscore.txt");
}

void Game::setCurrentLevel(int currentLevel) 
{
    m_currentLevel = currentLevel;
    g_gameStateMachine->changeState(new PlayState());
    m_levelComplete = false;
}

void Game::resetGame() 
{
    m_currentLevel = 1;
    m_levelComplete = false;
    m_Score = 0;
    m_continue = false;
    m_playerLives = 3;
    upgradeCurrentScore(0);
}

void Game::saveGameStats() 
{
    saveStats("assets/stats.txt", m_Score, m_playerLives, m_currentLevel, m_levelComplete);
}

void Game::loadGameStats() 
{
    m_playerLives = getStats("assets/stats.txt")[1];
    int score = getStats("assets/stats.txt")[0];
    m_currentLevel = getStats("assets/stats.txt")[2];
    m_levelComplete = getStats("assets/stats.txt")[3];
    upgradeCurrentScore(score);
}
