#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"
#include "Vector2.h"
#include <unordered_map>
using namespace HAPISPACE;

class Sprite;
class Visualisation
{
private:
	//Set screen width and height, do not change on pain of death.
	int screenWidth = 1024;
	int screenHeight = 1024;

	//An unordered map used to store the sprites within the Visualisation class.
	std::unordered_map<std::string, Sprite*> m_spriteMap;

	BYTE* screenPnter;
	Rectangle screenRect = Rectangle(screenWidth, screenHeight);

public:
	Visualisation();
	~Visualisation();

	//Currently the game only accounts for 1024x1024.
	//All getters for screenWidth/screenHeight, screen pointer and screen rectangle.
	int getScreenWidth() const { return screenWidth; }
	int getScreenHeight() const { return screenHeight; }
	BYTE* getScreenPointer() { return screenPnter; }
	Rectangle getScreenRect() const { return screenRect; }

	//Different colour clear functions.
	void greyClear(int greyVal);
	void slowColourClear(HAPI_TColour screenCol);
	void fastColourClear(HAPI_TColour screenCol);

	//Blitting functions:
	//BlitMemcpy - renders a texture by copying the entire line of texture data and pasting it directly to the screen space, no alpha changes used.
	//BlitAlpha - renders a texture by copying pixel by pixel the texture data and pasting it to the screen space, adjusting for the change in alpha.
	//BlitAlphaChanger - renders a texture by copying pixel by pixel the texture data and pasting it to the screen space, adjusting for the change in alpha.
	//					 This one also allows for functionality to change the overall alpha of the texture.
	//clipBlit - renders a texture, similar to BlitAlpha, except when it is rendered at the edge of the screen it will reduce the texture's size to only
	//			 render a part of the texture that is on the screen, and does not render it at all if it is off screen.
	void BlitMemcpy(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY);
	void BlitAlpha(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY);
	void BlitAlphaChanger(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY, BYTE alphaChange);
	void clipBlit(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY);

	//Sprite functions:
	//createSprite - a function to create a sprite, giving it a unique name and the number of frames within the texture
	//renderSprite - a function to render a sprite at the given position and the current frame number (to offset the frame rectangle)
	//renderSpriteFast - a function to render a sprite at the given position, without regards to frames or alpha changes (mainly used for background).
	bool createSprite(const std::string& filename, const std::string& uniqueName, int numFrames = 1);
	void renderSprite(const std::string& uniqueName, int posX, int posY, int frameNum = 0) const;
	void renderSpriteFast(const std::string& uniqueName, int posX, int posY);

	//Function to return the rectangle of the unique tagged sprite.	
	Rectangle Visualisation::getRectangle(const std::string& uniqueName) const;
};

