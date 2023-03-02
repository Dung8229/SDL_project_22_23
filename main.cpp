//Using SDL, SDL_image, standard IO, math, and strings
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Ship.h"
#include "Background.h"
#include "Asteroid.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

Background gBG;
Ship gShip;
Asteroid gOriginAsteroid;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Asteroid Reborn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
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
	//Loading success flag
	bool success = true;

	//Load ship
	if( !gShip.loadFromFile(gRenderer, "Resources/Ship.png" ) )
	{
		printf( "Failed to load ship texture!\n" );
		success = false;
	}

	else gShip.SetPos();

	//Load background texture
	if( !gBG.loadFromFile(gRenderer, "Resources/background.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gShip.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
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

			//While application is running
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

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render BG
				gBG.spinBackground(0.1);
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
                count1s+=3;
                if (count1s >= 1000) {
                    gOriginAsteroid.addAsteroid(gRenderer);
                    count1s -= 1000;
                }
                gOriginAsteroid.moveAsteroid(gRenderer);
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


