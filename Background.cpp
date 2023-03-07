#include "Background.h"

Background::Background() {
    x = -1177;
    y = -480;
    center.x = 1080;
    center.y = 1080;
    angle = 0;
    life = 1;
    rect.w = 0;
    rect.h = 0;
}

Background::~Background() {
    free();
}

void Background::spinBackground(double speed) {
    angle += speed;
}

int Background::getX() {
    return x;
}

int Background::getY() {
    return y;
}

double Background::getAngle() {
    return angle;
}

SDL_Point Background::getCenter() {
    return center;
}
