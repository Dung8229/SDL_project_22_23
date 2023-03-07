#include "Bullet.h"

bullet::bullet() {
    x = 0;
    y = 0;
    angle = 0;
    life = 1;
}

bullet::~bullet() {
    free();
}

void bullet::move() {
    x += SDL_cos(angle * 0.017453) * 2;
    y += SDL_sin(angle * 0.017453) * 2;
    if (x > 800 || x < -10 || y > 600 || y < -10) {
        life = 0;
    }
    rect.x = x;
    rect.y = y;
}

double bullet::getX() {
    return x;
}

double bullet::getY() {
    return y;
}

double bullet::getAngle() {
    return angle;
}

void bullet::setStartPos(double _x, double _y, double _angle) {
    x = _x + SDL_cos(_angle * 0.017453) * 40;
    y = _y + SDL_sin(_angle * 0.017453) * 40;
    angle = _angle;
}
