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

void Asteroid::setRect()
{
    if (life == 2)
    {
        if ( (angle > 0 && angle <= 90) || (angle > 180 && angle <= 270) )
        {
            rect.x = x + 3;
            rect.y = y;
            rect.w = mWidth - 10;
            rect.h = mHeight - 10;
        }
        else
        {
            rect.x = x - (mHeight - mWidth) / 2;
            rect.y = y + (mHeight - mWidth) / 2;
            rect.w = mHeight - 10;
            rect.h = mWidth - 10;
        }
    }
    else
    {
        rect.x = x;
        rect.y = y;
        rect.w = mWidth - 5;
        rect.h = mHeight - 5;
    }
}

double Asteroid::getX() {return x;}

double Asteroid::getY() {return y;}

double Asteroid::getDy() {return dy;}

double Asteroid::getDx() {return dx;}

double Asteroid::getAngle() {return angle;}

void Asteroid::setAsteroidList(vector<Asteroid*> _pAsteroidList) {
    pAsteroidList = _pAsteroidList;
}

vector<Asteroid*> Asteroid::getAsteroidList() {return pAsteroidList;}

void Asteroid::initAsteroid(SDL_Renderer* gRenderer) {
    Asteroid* newAsteroid = new Asteroid();
    switch (rand() % 3)
    {
        case 0:
            newAsteroid->life = 1;
            break;
        case 1:
            newAsteroid->life = 2;
            break;
        case 2:
            newAsteroid->life = 3;
            break;
    }
    if (newAsteroid->getLife() == 3) newAsteroid->loadFromFile(gRenderer, "Resources/BigAsteroid.png");
    else if (newAsteroid->getLife() == 2) newAsteroid->loadFromFile(gRenderer, "Resources/NormalAsteroid.png");
    else if (newAsteroid->getLife() == 1) newAsteroid->loadFromFile(gRenderer, "Resources/SmallAsteroid.png");
    switch (rand() % 2)
    {
        case 0:
            newAsteroid->setStartPos(rand() % SCREEN_WIDTH, -220, rand() % 360);
            break;
        case 1:
            newAsteroid->setStartPos(-220, rand() % SCREEN_HEIGHT, rand() % 360);
            break;
    }
    switch (rand() % 4)
    {
        case 0:
            newAsteroid->setDirection(getRandDirect(20), getRandDirect(20));
            break;
        case 1:
            newAsteroid->setDirection(-getRandDirect(20), getRandDirect(20));
            break;
        case 2:
            newAsteroid->setDirection(getRandDirect(20), -getRandDirect(20));
            break;
        case 3:
            newAsteroid->setDirection(-getRandDirect(20), -getRandDirect(20));
            break;
    }
    switch (rand() % 2)
    {
        case 0:
            newAsteroid->setRotation(getRandDirect(20));
            break;
        case 1:
            newAsteroid->setRotation(-getRandDirect(20));
            break;
    }
    pAsteroidList.push_back(newAsteroid);
}

void Asteroid::addAsteroid(SDL_Renderer* gRenderer, int type, double xPos, double yPos, double _dx, double _dy)
{
    Asteroid* firstAsteroid = new Asteroid();
    Asteroid* secondAsteroid = new Asteroid();
    firstAsteroid->setLife(type);
    secondAsteroid->setLife(type);
    if (type == 2)
    {
        firstAsteroid->loadFromFile(gRenderer, "Resources/NormalAsteroid.png");
        secondAsteroid->loadFromFile(gRenderer, "Resources/NormalAsteroid.png");
    }
    else if (type == 1)
    {
        firstAsteroid->loadFromFile(gRenderer, "Resources/SmallAsteroid.png");
        secondAsteroid->loadFromFile(gRenderer, "Resources/SmallAsteroid.png");
    }
    firstAsteroid->setStartPos(xPos, yPos, rand() % 360);
    secondAsteroid->setStartPos(xPos, yPos, rand() % 360);
    _dy = -_dy;
    double r = sqrt(_dx*_dx+_dy*_dy);
    double currentAngle;
    if (_dy > 0) currentAngle = SDL_acos(_dx / r);
    else currentAngle = 360 * DEG_TO_RAD - SDL_acos(_dx / r);
    firstAsteroid->setDirection( r * SDL_cos(currentAngle + 90 * DEG_TO_RAD), -r * SDL_sin(currentAngle + 90 * DEG_TO_RAD) );
    secondAsteroid->setDirection( r * SDL_cos(currentAngle - 90 * DEG_TO_RAD), -r * SDL_sin(currentAngle - 90 * DEG_TO_RAD) );
    switch (rand() % 2)
    {
        case 0:
            firstAsteroid->setRotation(getRandDirect(20));
            secondAsteroid->setRotation(-getRandDirect(20));
            break;
        case 1:
            firstAsteroid->setRotation(-getRandDirect(20));
            secondAsteroid->setRotation(getRandDirect(20));
            break;
    }
    pAsteroidList.push_back(firstAsteroid);
    pAsteroidList.push_back(secondAsteroid);
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
                pAsteroidList[i]->setRect();
                //SDL_Rect testRec = pAsteroidList[i]->getRect();
                //SDL_RenderFillRect(gRenderer, &testRec);
                pAsteroidList[i]->render(gRenderer, pAsteroidList[i]->x, pAsteroidList[i]->y, NULL, pAsteroidList[i]->angle, NULL, SDL_FLIP_NONE);
            }
            else
            {
                pAsteroidList.erase(pAsteroidList.begin() + i);
            }
            int outBorder = -sqrt(pAsteroidList[i]->mWidth*pAsteroidList[i]->mWidth+pAsteroidList[i]->mHeight*pAsteroidList[i]->mHeight);
            if (pAsteroidList[i]->x < outBorder ) pAsteroidList[i]->x = 800;
            if (pAsteroidList[i]->x > 800) pAsteroidList[i]->x = outBorder;
            if (pAsteroidList[i]->y < outBorder ) pAsteroidList[i]->y = 600;
            if (pAsteroidList[i]->y > 600) pAsteroidList[i]->y = outBorder;
            if (pAsteroidList[i]->angle > 360) pAsteroidList[i]->angle -= 360;
            if (pAsteroidList[i]->angle < 0) pAsteroidList[i]->angle += 360;
        }
    }
}

double getRandDirect(double divide) {
    double randDirect = (rand() % 5) + 5;
    randDirect /= divide;
    return randDirect;
}
