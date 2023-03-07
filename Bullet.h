#ifndef BULLET_H_
#define BULLET_H_

#include "BaseObject.h"

class bullet : public BaseObject {
private:
    double x, y;
    double angle;

public:
    bullet();
    ~bullet();
    double getX();
    double getY();
    double getAngle();
    void setStartPos(double _x, double _y, double _angle);
    void move();
};
#endif // BULLET_H_
