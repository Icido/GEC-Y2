#include "Visualisation.h"
#include "Sprite.h"
#include <algorithm>
#include <ostream>

Visualisation::Visualisation()
{
	if (!HAPI.Initialise(screenWidth, screenHeight, "Video game"))
		return;

	screenPnter = HAPI.GetScreenPointer();
}

Visualisation::~Visualisation()
{
	for (auto & p : m_spriteMap)
	{
		delete p.second;
	}
}

void Visualisation::greyClear(int greyVal)
{
	memset(screenPnter, greyVal, screenWidth * screenHeight * 4);
}

void Visualisation::slowColourClear(HAPI_TColour screenCol)
{
	for (int pixel = 0; pixel < screenWidth*screenHeight*4; pixel+=4)
	{
		screenPnter[pixel] = screenCol.red; //red
		screenPnter[pixel + 1] = screenCol.green; //green
		screenPnter[pixel + 2] = screenCol.blue; //blue
	}
}

void Visualisation::fastColourClear(HAPI_TColour screenCol)
{
	HAPI_TColour buffer[4];

	memcpy(buffer, &screenCol, 4);
	memcpy(buffer + 1, &screenCol, 4);
	memcpy(buffer + 2, &screenCol, 4);
	memcpy(buffer + 3, &screenCol, 4);

	BYTE *temp{ screenPnter };
	BYTE *end{ screenPnter + screenWidth * screenHeight * 4 };

	while (temp < end)
	{
		memcpy(temp, buffer, 4 * 4);
		temp += 4 * 4;
	}
}

void Visualisation::BlitMemcpy(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY)
{
	//Creating temporary pointers
	BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;
	BYTE *sourcePointer = source;

	for (int y = 0; y < sourceRect.Height(); y++)
	{
		memcpy(destPointer, sourcePointer, sourceRect.Width() * 4);

		//Move source pointer to the next line
		sourcePointer += sourceRect.Width() * 4;

		//Move destination pointer to the next line
		destPointer += destRect.Width() * 4;
	}
}

void Visualisation::BlitAlpha(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY)
{
	//Creating temporary pointers
	BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;
	BYTE *sourcePointer = source;
	int endOfLineIncrement = (destRect.Width() - sourceRect.Width()) * 4;

	//Loops over the height of the texture
	for (int y = 0; y < sourceRect.Height(); y++)
	{
		//Loops over the width of the texture
		for (int x = 0; x < sourceRect.Width(); x++)
		{
			BYTE alpha = sourcePointer[3];

			//Checks if the alpha of the current texture pixel is NOT 0. If it is 0, move to the next texture pixel.
			if (alpha != 0)
			{
				//Checks if the alpha of the current texture pixel is exactly 255. If it is, memcpy it regardless of alpha, else alpha blend 
				//the source and texture pixels together.
				if (alpha == 255)
				{
					memcpy(destPointer, sourcePointer, 4);
				}
				else
				{
					BYTE blue = sourcePointer[0];
					BYTE green = sourcePointer[1];
					BYTE red = sourcePointer[2];

					destPointer[0] = destPointer[0] + ((alpha*(blue - destPointer[0])) >> 8);
					destPointer[1] = destPointer[1] + ((alpha*(green - destPointer[1])) >> 8);
					destPointer[2] = destPointer[2] + ((alpha*(red - destPointer[2])) >> 8);
				}
			}
			destPointer += 4;
			sourcePointer += 4;
		}
		destPointer += endOfLineIncrement;
	}
}

void Visualisation::BlitAlphaChanger(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY, BYTE alphaChange)
{
	//Creating temporary pointers
	BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;
	BYTE *sourcePointer = source;
	int endOfLineIncrement = (destRect.Width() - sourceRect.Width()) * 4;

	//Loops over the height of the texture
	for (int y = 0; y < sourceRect.Height(); y++)
	{
		//Loops over the width of the texture
		for (int x = 0; x < sourceRect.Width(); x++)
		{
			//This is where the alphaChange is used to change the alpha of the entire texture by the input value.
			BYTE alpha = (BYTE)(sourcePointer[3] * (alphaChange / 255.f));

			//These if statements clamp the alpha value to between 0 and 255.
			if (alpha > 255)
			{
				alpha = 255;
			}

			if (alpha < 0)
			{
				alpha = 0;
			}

			//Checks if the alpha of the current texture pixel is NOT 0. If it is 0, move to the next texture pixel.
			if (alpha != 0)
			{
				//Checks if the alpha of the current texture pixel is exactly 255. If it is, memcpy it regardless of alpha, else alpha blend 
				//the source and texture pixels together.
				if (alpha == 255)
				{
					memcpy(destPointer, sourcePointer, 4);
				}
				else
				{
					BYTE blue = sourcePointer[0];
					BYTE green = sourcePointer[1];
					BYTE red = sourcePointer[2];

					destPointer[0] = destPointer[0] + ((alpha*(blue - destPointer[0])) >> 8);
					destPointer[1] = destPointer[1] + ((alpha*(green - destPointer[1])) >> 8);
					destPointer[2] = destPointer[2] + ((alpha*(red - destPointer[2])) >> 8);
				}
			}
			destPointer += 4;
			sourcePointer += 4;
		}
		destPointer += endOfLineIncrement;
	}
}

void Visualisation::clipBlit(BYTE *dest, const Rectangle &destRect, BYTE *source, const Rectangle &sourceRect, int posX, int posY)
{
	Rectangle clipRect(sourceRect.Width(), sourceRect.Height());
	clipRect.translate(posX, posY);

	//If the sourceRect is NOT completely outside the destRect, continue to blit.
	//If it is outside, do nothing
	if (!clipRect.isCompletelyOutsideOf(destRect))
	{
		//If the sourceRect is NOT completely inside the destRect, start the clipping.
		//If it is inside, blit normally
		if (!clipRect.isCompletelyContainedBy(destRect))
		{
			clipRect.clipTo(destRect);
			clipRect.translate(-posX, -posY);
			posX = std::max(0, posX);
			posY = std::max(0, posY);

			//New pointers and end of line increments to compensate for the clipped texture.
			BYTE *sourcePointer = source + (clipRect.getLeft() + clipRect.getTop()*sourceRect.Width()) * 4;
			BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;

			int endOfLineDestIncrement = (destRect.Width() - clipRect.Width()) * 4;
			int endOfLineSourceIncrement = (sourceRect.Width() - clipRect.Width()) * 4;
			
			for (int y = 0; y < clipRect.Height(); y++)
			{
				for (int x = 0; x < clipRect.Width(); x++)
				{
					BYTE alpha = sourcePointer[3];

					if (alpha != 0)
					{
						if (alpha == 255)
						{
							memcpy(destPointer, sourcePointer, 4);
						}
						else
						{
							BYTE blue = sourcePointer[0];
							BYTE green = sourcePointer[1];
							BYTE red = sourcePointer[2];

							destPointer[0] = destPointer[0] + ((alpha*(blue - destPointer[0])) >> 8);
							destPointer[1] = destPointer[1] + ((alpha*(green - destPointer[1])) >> 8);
							destPointer[2] = destPointer[2] + ((alpha*(red - destPointer[2])) >> 8);
						}
					}
					destPointer += 4;
					sourcePointer += 4;
				}
				destPointer += endOfLineDestIncrement;
				sourcePointer += endOfLineSourceIncrement;
			}
		}
		else
		{
			BlitAlpha(dest, destRect, source, sourceRect, posX, posY);
		}
	}
}

bool Visualisation::createSprite(const std::string& filename, const std::string& uniqueName, int numFrames /* = 1*/)
{
	//Expects the user to know how many frames of animation are within the texture.
	Sprite *sprite = new Sprite();
	if (!sprite->LoadTexture(filename, numFrames))
	{
		//Error
		std::cerr << "Texture was unable to be loaded" << std::endl;
		delete sprite;
		return false;
	}
	m_spriteMap[uniqueName] = sprite;
	return true;
}

void Visualisation::renderSprite(const std::string& uniqueName, int posX, int posY, int frameNum /* = 0 */) const
{
	//Animates the texture assuming that the sprites are ordered horizontally.
	if (m_spriteMap.find(uniqueName) == m_spriteMap.end())
	{
		//Error
		std::cerr << "Texture was unable to be rendered" << std::endl;
		HAPI.UserMessage("Texture was not loaded! Could not render!", "Warning: No texture found!");
		HAPI.Close();
	}
	m_spriteMap.at(uniqueName)->RenderTexture(uniqueName, screenRect, screenPnter, posX, posY, frameNum);
}

void Visualisation::renderSpriteFast(const std::string& uniqueName, int posX, int posY)
{
	if (m_spriteMap.find(uniqueName) == m_spriteMap.end())
	{
		//Error
		std::cerr << "Texture was unable to be rendered" << std::endl;
		HAPI.UserMessage("Texture was not loaded! Could not render!", "Warning: No texture found!");
		HAPI.Close();
	}
	m_spriteMap.at(uniqueName)->RenderTextureFast(uniqueName, screenRect, screenPnter, posX, posY);
}

Rectangle Visualisation::getRectangle(const std::string& uniqueName) const
{
	if (m_spriteMap.find(uniqueName) == m_spriteMap.end())
	{
		//Error
		std::cerr << "Texture was unable to be rendered" << std::endl;
		HAPI.UserMessage("Texture was not loaded! Could not render!", "Warning: No texture found!");
		HAPI.Close();
	}
	return m_spriteMap.at(uniqueName)->getRectangle(uniqueName);

}

