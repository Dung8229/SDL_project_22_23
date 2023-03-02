#include "Asteroid.h"

Asteroid::Asteroid() {
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
    angle = 0;
    dAngle = 0;
    life = 1;
}

Asteroid::~Asteroid() {
    free();
}

void Asteroid::setStartPos(double _x, double _y, double _angle) {
    x = _x;
    y = _y;
    angle = _angle;
}

void Asteroid::setDirection(double _dx, double _dy) {
    dx = _dx;
    dy = _dy;
}

void Asteroid::setRotation(double _dAngle) {
    dAngle = _dAngle;
}

double Asteroid::getX() {
    return x;
}

double Asteroid::getY() {
    return y;
}

double Asteroid::getAngle() {
    return angle;
}

void Asteroid::setAsteroidList(vector<Asteroid*> _pAsteroidList) {
    pAsteroidList = _pAsteroidList;
}

vector<Asteroid*> Asteroid::getAsteroidList() {
    return pAsteroidList;
}

void Asteroid::addAsteroid(SDL_Renderer* gRenderer) {
    Asteroid* newAsteroid = new Asteroid();
    newAsteroid->loadFromFile(gRenderer, "Resources/BigAsteroid1.png");
    switch (rand() % 2)
    {
        case 0:
            newAsteroid->setStartPos(rand() % SCREEN_WIDTH, -100, rand() % 360);
            break;
        case 1:
            newAsteroid->setStartPos(-100, rand() % SCREEN_HEIGHT, rand() % 360);
            break;
    }
    switch (rand() % 4)
    {
        case 0:
            newAsteroid->setDirection(getRandDirect(), getRandDirect());
            break;
        case 1:
            newAsteroid->setDirection(-getRandDirect(), getRandDirect());
            break;
        case 2:
            newAsteroid->setDirection(getRandDirect(), -getRandDirect());
            break;
        case 3:
            newAsteroid->setDirection(-getRandDirect(), -getRandDirect());
            break;
    }
    switch (rand() % 2)
    {
        case 0:
            newAsteroid->setRotation(getRandDirect());
            break;
        case 1:
            newAsteroid->setRotation(-getRandDirect());
            break;
    }
    pAsteroidList.push_back(newAsteroid);
}

void Asteroid::moveAsteroid(SDL_Renderer* gRenderer) {
    for (int i = 0; i < pAsteroidList.size(); i++) {
        if (pAsteroidList[i] != NULL)
        {
            if (pAsteroidList[i]->life > 0)
            {
                pAsteroidList[i]->x += pAsteroidList[i]->dx;
                pAsteroidList[i]->y += pAsteroidList[i]->dy;
                pAsteroidList[i]->angle += pAsteroidList[i]->dAngle;
                pAsteroidList[i]->render(gRenderer, pAsteroidList[i]->x, pAsteroidList[i]->y, NULL, pAsteroidList[i]->angle, NULL, SDL_FLIP_NONE);
            }
            else
            {
                pAsteroidList.erase(pAsteroidList.begin() + i);
            }
            if (pAsteroidList[i]->x < -100 ) pAsteroidList[i]->x = 800;
            if (pAsteroidList[i]->x > 800) pAsteroidList[i]->x = -100;
            if (pAsteroidList[i]->y < -100 ) pAsteroidList[i]->y = 600;
            if (pAsteroidList[i]->y > 600) pAsteroidList[i]->y = -100;
        }
    }
}

double getRandDirect() {
    double randDirect = (rand() % 20) / 10.0;
    if (randDirect < 0.5) randDirect++;
    return randDirect;
}
