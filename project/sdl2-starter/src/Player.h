
#ifndef __Player__
#define __Player__

#include "ShooterObject.h"

class Player: public ShooterObject 
{
private:
    // bring the player back if there are lives left
    void ressurect();
    
    // handle any input from the keyboard, mouse, or joystick
    void handleInput();
    
    // handle any animation for the player
    void handleAnimation();

    // player can be invulnerable for a time
    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
public:
    Player();
    virtual ~Player() {}
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision();
    virtual string type() { return "Player"; }

};

class PlayerCreator : public BaseCreator 
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif // define __Player__