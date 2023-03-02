#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "BaseObject.h"

class Background : public BaseObject {
private:
    int x;
    int y;
    SDL_Point center;
    double angle;
public:
    Background();
    ~Background();
    int getX();
    int getY();
    double getAngle();
    SDL_Point getCenter();
    void spinBackground(double speed);
};
#endif // BACKGROUND_H_
