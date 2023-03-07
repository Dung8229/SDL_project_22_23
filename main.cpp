//Using SDL, SDL_image, standard IO, math, and strings
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Ship.h"
#include "Background.h"
#include "Asteroid.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init();

bool loadMedia();

void close();

bool isCollide(SDL_Rect a, SDL_Rect b);

Background gBG;
Ship gShip;
Asteroid gBaseAsteroid;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Asteroid Reborn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if( !gShip.loadFromFile(gRenderer, "Resources/Ship.png" ) )
	{
		printf( "Failed to load ship texture!\n" );
		success = false;
	}

	else gShip.SetPos();

	if( !gBG.loadFromFile(gRenderer, "Resources/background.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	//Load music
    gMusic = Mix_LoadMUS( "Resources/Sound/AsteroidTrack.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

	return success;
}

void close()
{
	gShip.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool isCollide(SDL_Rect a, SDL_Rect b)
{
    if( a.y + a.h <= b.y ) return false;
    if( a.y >= b.y + b.h ) return false;
    if( a.x + a.w <= b.x ) return false;
    if( a.x >= b.x + b.w ) return false;
    return true;
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			SDL_Point BGcenter = gBG.getCenter();

			double count = 1000;
			double vCount = 1;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
				    if( Mix_PlayingMusic() == 0 )
                    {
                        //Play the music
                        Mix_PlayMusic( gMusic, -1 );
                    }
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if ( e.type == SDL_KEYDOWN)
                    {
                        if ( e.key.keysym.sym == SDLK_p )
                        {
                            /*//If there is no music playing
                            if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMusic, -1 );
                            }
                            //If music is being played
                            else
                            {*/
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
                            //}
                        }
                    }
                    gShip.HandleKeyboard(gRenderer, e);
				}
				gShip.MoveForward();
				gShip.Rotate();
				//SDL_Rect testRec = gShip.getRect();

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				gBG.spinBackground(0.05);
                gBG.render(gRenderer, gBG.getX(), gBG.getY(), NULL, gBG.getAngle(), &BGcenter, flipType);
				//Render ship
				//SDL_RenderFillRect(gRenderer, &testRec);
				gShip.render(gRenderer, gShip.getX(), gShip.getY(), NULL, gShip.getAngle(), NULL, flipType );
                //Render bullet
                vector<Asteroid*> AsteroidList = gBaseAsteroid.getAsteroidList();
                vector<bullet*> bulletList = gShip.getBulletList();
                for (int i = 0; i < AsteroidList.size(); i++)
                {
                    Asteroid* gAsteroid = AsteroidList[i];
                    for (int j = 0; j < bulletList.size(); j++)
                    {
                        bullet* gBullet = bulletList[j];
                        if (gBullet != NULL)
                        {
                            if (gBullet->getLife() > 0)
                            {
                                gBullet->move();
                                if ( isCollide( gAsteroid->getRect(), gBullet->getRect() ) )
                                {
                                    gBaseAsteroid.addAsteroid(gRenderer, gAsteroid->getLife() - 1, gAsteroid->getX(), gAsteroid->getY(), gAsteroid->getDx(), gAsteroid->getDy());
                                    gAsteroid->setLife(0);
                                    gBullet->setLife(0);
                                }
                                gBullet->render(gRenderer, gBullet->getX(), gBullet->getY(), NULL, gBullet->getAngle(), NULL, flipType);
                            }
                            else
                            {
                                bulletList.erase(bulletList.begin() + j);
                                gShip.setBulletList(bulletList);
                                delete gBullet;
                                gBullet = NULL;
                            }
                        }
                    }
                    if ( isCollide(gShip.getRect(), gAsteroid->getRect() ) )
                    {
                        gShip.setLife(gShip.getLife() - 1);
                        if (gShip.getLife() > 0)
                        {
                            gShip.SetPos();
                        }
                        else quit = true;
                    }
                }
                //Render asteroid
                count += vCount;
                if (count >= 1000) {
                    gBaseAsteroid.initAsteroid(gRenderer);
                    count -= 1000;
                    vCount += 0.1;
                }
                gBaseAsteroid.moveAsteroid(gRenderer);

				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}




