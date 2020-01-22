#include "PixelCollider.h"

PixelCollider::PixelCollider() {};
PixelCollider::~PixelCollider() {};

std::vector<RectFloat*> PixelCollider::getColliders()
{
	return colliders;
}

void PixelCollider::move(float x, float y)
{
	int count = colliders.size();
	posX += x;
	posY += y;
	for (int i = 0; i < count; i++)
	{
		colliders[i]->x += x;
		colliders[i]->y += y;
	}
}


SDL_Texture* PixelCollider::createCollider(SDL_Renderer* rend, const char* path, const SDL_Rect& srcRect, int alphaValue)
{
	free(NULL);
	posX = srcRect.x;
	posY = srcRect.y;
	
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			int i = formattedSurface->w;
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
				int mWidth, mHeight;
				void* mPixels;
				int mPitch;
				//Lock texture for manipulation
				//SDL_Delay(1000);
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch);

				//Copy loaded/formatted surface pixels
				memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)mPixels;

				float scaleX = (float)srcRect.w / (float)mWidth;
				float scaleY = (float)srcRect.h / (float)mHeight;

				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0, 0, 0, 0);

				bool startRect = false;
				int counter = 0;
				int pixelStartX = 0;

				for (int y = 0; y < mHeight; y++)
				{
					for (int x = 0; x < mWidth; x++)
					{

						Uint8 r, g, b, a;
						SDL_GetRGBA(pixels[counter], formattedSurface->format, &r, &g, &b, &a);

						//checking for alpha
						if (a < alphaValue)
						{
							if (startRect) //last pixel was colour, this pixil is alpha
							{
								startRect = false;
								RectFloat* rect = new RectFloat{};
								rect->x = srcRect.x + (pixelStartX * scaleX);
								rect->y = srcRect.y + (y * scaleY);
								rect->w = (x - pixelStartX) * scaleX;
								rect->h = 1 * scaleY;
								colliders.push_back(rect);
							}
						}
						else // color
						{
							if (!startRect)
							{
								startRect = true;
								pixelStartX = x;
							}
						}
						counter++;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				mPixels = NULL;
				delete(mPixels);
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	//mTexture = newTexture;
	if (newTexture == nullptr)
	{
		return nullptr;
	}
	return newTexture;
}

void PixelCollider::setPos(float x, float y)
{
	int count = colliders.size();	
	
	for (int i = 0; i < count; i++)
	{
		float offsetX = posX - x;
		float offsetY = posY - y;
		colliders[i]->x -=  offsetX;
		colliders[i]->y -=  offsetY;
		
	}
	posX = x;
	posY = y;
}

float PixelCollider::getPosX()
{
	return posX;
}

float PixelCollider::getPosY()
{
	return posY;
}

