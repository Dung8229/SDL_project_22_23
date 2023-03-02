#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
	public:
		BaseObject();
		~BaseObject();
		bool loadFromFile(SDL_Renderer* gRenderer, std::string path );
		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();

    protected:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;

		int life;
};

#endif // BASE_OBJECT_H_

