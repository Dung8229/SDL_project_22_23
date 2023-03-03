#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "BaseObject.h"
#include <cstdlib>

double getRandDirect(double divide);

class Asteroid : public BaseObject {
private:
    double x, y, angle;
    double dx, dy, dAngle;
    vector<Asteroid*> pAsteroidList;
public:
    Asteroid();
    ~Asteroid();
    void setStartPos(double _x, double _y, double _angle);
    void setDirection(double _dx, double _dy);
    void setRotation(double _dAngle);
    double getX();
    double getY();
    double getAngle();
    void setAsteroidList(vector<Asteroid*> _pAsteroidList);
    vector<Asteroid*> getAsteroidList();
    void addAsteroid(SDL_Renderer* gRenderer);
    void moveAsteroid(SDL_Renderer* gRenderer);
};
#endif // ASTEROID_H_
