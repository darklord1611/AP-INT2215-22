#ifndef __Layer__
#define __Layer__

class Layer 
{
protected:
    virtual ~Layer() {}
public:
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif // define __Layer__