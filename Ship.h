#ifndef SHIP_H_
#define SHIP_H_

#include "BaseObject.h"
#include "Bullet.h"

class Ship: public BaseObject {
protected:
    double x, y;
    double dxShip, dyShip;
    bool SpeedUp;

    double angle;
    bool turnRight;
    bool turnLeft;
    double dBeta;

    vector<bullet*> pBulletList;

public:
    Ship();
    ~Ship();
    double getX();
    double getY();
    double getAngle();
    void setBulletList(vector<bullet*> _pBulletList);
    vector<bullet*> getBulletList();
    void MoveForward();
    void Rotate();
    void SetPos();
    void HandleKeyboard(SDL_Renderer* gRenderer, SDL_Event e);
};
#endif // SHIP_H_
