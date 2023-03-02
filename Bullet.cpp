#include "Bullet.h"

bullet::bullet() {
    x = 0;
    y = 0;
    angle = 0;
    rect.x = x;
    rect.y = y;
    rect.w = mWidth;
    rect.h = mHeight;
    moving = true;
    life = 1;
}

bullet::~bullet() {
    free();
}

void bullet::setRect(double _x, double _y) {
    rect.x = _x;
    rect.y = _y;
}

void bullet::setMove(bool state) {
    moving = state;
}

bool bullet::isMoving() {
    return moving;
}
void bullet::move(int xBorder, int yBorder) {
    x += SDL_cos(angle * 0.017453) * 4;
    y += SDL_sin(angle * 0.017453) * 4;
    if (x > xBorder || x < 0 || y > yBorder || y < 0) {
        moving = false;
    }
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
