#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"
#include <algorithm>
using namespace HAPISPACE;
class Sprite
{
	//Animation type enum class to determine how the sprite's animation sheet is layed out (unused)
	enum class AnimationType
	{
		vertical, horizontal
	};

private:
BYTE* texturePnter{ nullptr };
	Rectangle textRect;
	Rectangle frameRect;
	int numFrames{ 1 };

	//(Unused)
	AnimationType animType;

public:
	Sprite();
	~Sprite();

	//Sets the animation type of the current sprite to either vertical or horizontal (unused)
	AnimationType setType(AnimationType newType) { animType = newType; }

	//Returns the animation type (unused)
	AnimationType getType() { return animType; }

	//Sets the texture rectangle to the rectangle parameter
	void setTextRect(Rectangle setRect)
	{
		textRect = setRect;
	}

	//Sets the frame rectangle to the rectangle parameter
	void setFrameRect(Rectangle setRect)
	{
		frameRect = setRect;
	}

	//Used to load a texture. Returns false if there is no texture at the directory used of the name given.
	bool LoadTexture(const std::string& name, int noFrames = 1);

	//Renders the loaded texture/frames with alpha blending implemented.
	void RenderTexture(const std::string& uniqueName, Rectangle destRect, BYTE* dest, int posX, int posY, int frameNum = 0);

	//Renders the entire texture with no blending.
	void RenderTextureFast(const std::string& uniqueName, Rectangle destRect, BYTE* dest, int posX, int posY);

	//Returns the rectangle from the given texture name.
	Rectangle getRectangle(const std::string& uniqueName) { return frameRect; }
};