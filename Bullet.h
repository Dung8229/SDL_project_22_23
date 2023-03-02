#ifndef BULLET_H_
#define BULLET_H_

#include "BaseObject.h"

class bullet : public BaseObject {
private:
    double x, y;
    double angle;
    SDL_Rect rect;
    bool moving;
public:
    bullet();
    ~bullet();
    void setRect(double _x, double _y);
    void setMove(bool state);
    bool isMoving();
    double getX();
    double getY();
    double getAngle();
    void setStartPos(double _x, double _y, double _angle);
    void move(int xBorder, int yBorder);
};
#endif // BULLET_H_
