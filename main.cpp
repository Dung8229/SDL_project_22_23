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

Background gBG;
Ship gShip;
Asteroid gOriginAsteroid;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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

	return success;
}

void close()
{
	gShip.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
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

			int count1s = 1000;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    else gShip.HandleKeyboard(gRenderer, e);
				}

				gShip.MoveForward();
				gShip.Rotate();

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				gBG.spinBackground(0.05);
                gBG.render(gRenderer, gBG.getX(), gBG.getY(), NULL, gBG.getAngle(), &BGcenter, flipType);
				//Render ship
				gShip.render(gRenderer, gShip.getX(), gShip.getY(), NULL, gShip.getAngle(), NULL, flipType );
                //Render bullet
                for (int i = 0; i < gShip.getBulletList().size(); i++) {
                    vector<bullet*> bulletList = gShip.getBulletList();
                    bullet* gBullet = bulletList[i];
                    if (gBullet != NULL)
                    {
                        if (gBullet->isMoving())
                        {
                            gBullet->move(800, 600);
                            gBullet->render(gRenderer, gBullet->getX(), gBullet->getY(), NULL, gBullet->getAngle(), NULL, flipType);
                        }
                        else
                        {
                            bulletList.erase(bulletList.begin() + i);
                            gShip.setBulletList(bulletList);
                            delete gBullet;
                            gBullet = NULL;
                        }
                    }
                }
                //Render asteroid
                count1s+=1;
                if (count1s >= 1000) {
                    gOriginAsteroid.addAsteroid(gRenderer);
                    count1s -= 1000;
                }
                gOriginAsteroid.moveAsteroid(gRenderer);

				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}


