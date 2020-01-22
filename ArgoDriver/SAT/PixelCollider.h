#ifndef PIXELCOLLIDER_H
#define PIXELCOLLIDER_H
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "RectFloat.h"

class PixelCollider
{
private:
	std::vector<RectFloat*> colliders;
	float posX;
	float posY;
public:
	PixelCollider();
	~PixelCollider();

	/*
	Takes a sdl_recnderer and path to image and load the texture.
	Sorcerect determine the scale of the object and starting postion.
	alphaValue is between 255 and 0. 255 means that all alpha will be cull from collision.
	*/
	SDL_Texture* createCollider(SDL_Renderer* rend, const char* imgPath,const SDL_Rect& srcRect, int alphaValue);

	/*
	Move the collider relative to the current postion. e.g. x += value, y+= value
	*/
	void move(float x, float y);

	/*
	Set the overall position of the collider. e.g x = value, y = value
	*/
	void setPos(float x, float y);


	std::vector<RectFloat*> getColliders();

	float getPosX();
	float getPosY();

};
#endif