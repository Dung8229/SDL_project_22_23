#include "Ship.h"

Ship::Ship() {
    x = 0;
    y = 0;
    dxShip = 0;
    dyShip = 0;
    angle = 0;
    SpeedUp = false;

    turnRight = false;
    turnLeft = false;
    dBeta = 0;

    life = 3;
}

Ship::~Ship() {
    free();
}

void Ship::MoveForward() {
    if (SpeedUp) {
        dxShip = SDL_cos(angle * 0.017453);
        dyShip = SDL_sin(angle * 0.017453);
    }
    else {
        dxShip *= 0.996;
        dyShip *= 0.996;
    }
    x += dxShip;
    y += dyShip;
    if (x < -mWidth ) x = 800;
    if (x > 800) x = -mWidth;
    if (y < -mHeight ) y = 600;
    if (y > 600) y = -mHeight;
    rect.x = x;
    rect.y = y;
}

void Ship::Rotate() {
    if (turnLeft) dBeta = -1.3;
    else if (turnRight) dBeta = 1.3;
    else {
        dBeta *= 0.985;
    }
    angle += dBeta;
}

void Ship::SetPos()
{
    x = ( 800 - mWidth ) / 2;
    y = ( 600 - mHeight ) / 2;
}

void Ship::HandleKeyboard(SDL_Renderer* gRenderer, SDL_Event e) {
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_RIGHT:
            turnRight = true;
            break;

            case SDLK_LEFT:
            turnLeft = true;
            break;

            case SDLK_UP:
            SpeedUp = true;
            break;

            case SDLK_SPACE:
            {
                bullet* newBullet = new bullet();
                newBullet->loadFromFile(gRenderer, "Resources/Bullet.png");
                newBullet->setStartPos(x, y + 8, angle);
                pBulletList.push_back(newBullet);
            }
            /*case SDLK_9:
            //If there is no music playing
            if( Mix_PlayingMusic() == 0 )
            {
                //Play the music
                Mix_PlayMusic( gMusic, -1 );
            }
            //If music is being played
            else
            {
                //If the music is paused
                if( Mix_PausedMusic() == 1 )
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                //If the music is playing
                else
                {
                    //Pause the music
                    Mix_PauseMusic();
                }
            }
            break;*/
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_RIGHT:
            turnRight = false;
            break;

            case SDLK_LEFT:
            turnLeft = false;
            break;

            case SDLK_UP:
            SpeedUp = false;
            break;
        }
    }
}

double Ship::getX() {
    return x;
}

double Ship::getY() {
    return y;
}

double Ship::getAngle() {
    return angle;
}

void Ship::setBulletList(vector<bullet*> _pBulletList) {
    pBulletList = _pBulletList;
}

vector<bullet*> Ship::getBulletList() {
    return pBulletList;
}
