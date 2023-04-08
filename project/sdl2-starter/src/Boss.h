#ifndef __Boss__
#define __Boss__

class Boss : public Enemy 
{
private:
    bool m_entered;
public:
    virtual ~Boss() {}
    Boss();
    virtual void collision();
    virtual void update();
    virtual void 
};
#endif 