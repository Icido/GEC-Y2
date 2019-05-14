#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	//Deletes the pointer to the texture of the current sprite when the sprite is destroyed.
	delete[] texturePnter;
}

bool Sprite::LoadTexture(const std::string& name, int noFrames/* = 1*/)
{
	int textWidth, textHeight;
	BYTE *pTexture{ nullptr };

	if (!HAPI.LoadTexture(name, &texturePnter, textWidth, textHeight))
	{
		HAPI.UserMessage("Texture " + name + " not loaded!", "Warning: No texture found!");
		return false;
	}

	numFrames = noFrames;
	Rectangle TextureRect(textWidth, textHeight);
	Rectangle FrameRect(textWidth, textHeight / noFrames);

	//TODO Make sure the sprite is animated differently depending on Horizontal or Vertical enum
	
	setTextRect(TextureRect);
	setFrameRect(FrameRect);
	std::cout << "Animated texture loaded in Sprite class" << std::endl;
	return true;
}

void Sprite::RenderTexture(const std::string& uniqueName, Rectangle destRect, BYTE* dest, int posX, int posY, int frameNum/* = 0 */)
{
	Rectangle clipRect(frameRect.Width(), frameRect.Height());
	clipRect.translate(posX, posY);

	//If the textRect is NOT completely outside the destRect, continue to blit.
	//If it is outside, do nothing
	if (!clipRect.isCompletelyOutsideOf(destRect))
	{
		//If the textRect is NOT completely inside the destRect, start the clipping.
		//If it is inside, blit normally
		if (!clipRect.isCompletelyContainedBy(destRect))
		{
			clipRect.clipTo(destRect);
			clipRect.translate(-posX, -posY);
			posX = std::max(0, posX);
			posY = std::max(0, posY);

			//New pointers and end of line increments to compensate for the clipped texture.
			BYTE *textPointer = texturePnter + ((clipRect.getLeft() + clipRect.getTop()*textRect.Width()) * 4) + (frameRect.Width() * frameRect.Height() * 4 * frameNum);
			BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;

			int endOfLineDestIncrement = (destRect.Width() - clipRect.Width()) * 4;
			int endOfLineTextIncrement = (textRect.Width() - clipRect.Width()) * 4;

			//Unknown reason why clipRect.Width within the x < clipRect.Width() was at 62.3% of runtime, therefore using this int w to reduce it dramatically.
			int w = clipRect.Width();
			for (int y = 0; y < clipRect.Height(); y++)
			{
				for (int x = 0; x < w; x++)
				{
					BYTE alpha = textPointer[3];

					if (alpha != 0)
					{
						if (alpha == 255)
						{
							memcpy(destPointer, textPointer, 4);
						}
						else
						{
							BYTE blue = textPointer[0];
							BYTE green = textPointer[1];
							BYTE red = textPointer[2];

							destPointer[0] = destPointer[0] + ((alpha*(blue - destPointer[0])) >> 8);
							destPointer[1] = destPointer[1] + ((alpha*(green - destPointer[1])) >> 8);
							destPointer[2] = destPointer[2] + ((alpha*(red - destPointer[2])) >> 8);
						}
					}
					destPointer += 4;
					textPointer += 4;
				}
				destPointer += endOfLineDestIncrement;
				textPointer += endOfLineTextIncrement;
			}
		}
		else
		{
			//Creating temporary pointers
			BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;
			BYTE *textPointer = texturePnter + (frameRect.Width() * frameRect.Height() * 4 * frameNum);
			int endOfLineIncrement = (destRect.Width() - textRect.Width()) * 4;

			for (int y = 0; y < clipRect.Height(); y++)
			{
				for (int x = 0; x < clipRect.Width(); x++)
				{
					BYTE alpha = textPointer[3];

					if (alpha != 0)
					{
						if (alpha == 255)
						{
							memcpy(destPointer, textPointer, 4);
						}
						else
						{
							BYTE blue = textPointer[0];
							BYTE green = textPointer[1];
							BYTE red = textPointer[2];

							destPointer[0] = destPointer[0] + ((alpha*(blue - destPointer[0])) >> 8);
							destPointer[1] = destPointer[1] + ((alpha*(green - destPointer[1])) >> 8);
							destPointer[2] = destPointer[2] + ((alpha*(red - destPointer[2])) >> 8);
						}
					}
					destPointer += 4;
					textPointer += 4;
				}
				destPointer += endOfLineIncrement;
			}
		}
	}
}

void Sprite::RenderTextureFast(const std::string& uniqueName, Rectangle destRect, BYTE* dest, int posX, int posY)
{
	//Creating temporary pointers
	BYTE *destPointer = dest + (posX + posY * destRect.Width()) * 4;
	BYTE *textPointer = texturePnter;

	for (int y = 0; y < textRect.Height(); y++)
	{
		memcpy(destPointer, textPointer, textRect.Width() * 4);

		//Move source pointer to the next line
		textPointer += textRect.Width() * 4;

		//Move destination pointer to the next line
		destPointer += destRect.Width() * 4;
	}
}
