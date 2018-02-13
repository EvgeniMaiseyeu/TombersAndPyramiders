#include "CharacterTestScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include <iostream>
#include "Camera.h"
#include "MovingSquare.h"
#include "MiscSquare.h"
#include <vector>
#include "SpawnManager.h"
#include <memory>
#include <WoodenLongbow.h>
#include "AudioManager.h"

CharacterTestScene::CharacterTestScene()
{
}

void CharacterTestScene::onStart()
{
	AudioManager::getInstance()->playMusic();
	Camera::getActiveCamera()->addComponent<CameraFollow>(Camera::getActiveCamera().get());

	const float size = 12;
	const float scale = 5;

	for (float x = 0; x <= size; x++)
	{
		for (float y = 0; y >= -size; y--)
		{
			float column = x * scale;
			float row = y * scale;

			// The offsets are to allow the tile art to overlap.
			float floorOffset = 0.56f;
			float wallOffset = 1.25f;

			// Create a floor tile. 
			SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset) , (y * -1) - 50, scale, "stoneTile.png");

			int xMod = (int)x % 3;
			int yMod = (int)y % 3;


			if (xMod == 0 && yMod == 0 && x != 0 && y != 0)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), (y * -1) - 50, scale, "table.png");
			}

			// Create our walls. A wall is half the size of a tile, so we need two. Each wall that gets created south of a previous wall
			// needs to have a higher z value so it ovelaps the previous wall.
			// Create top walls.
			if (y == 0)
			{
				// Create top left wall.
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row + (scale / 2) + floorOffset, y * -1, scale, "wallTopLeft.png");
					SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset, (y * -1) + 0.5, scale, "wallLeft.png");
				}
				// Create top right wall.
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row + (scale / 2) + floorOffset, y * -1, scale, "wallTopRight.png");
					SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png");
					SpawnManager::getInstance()->generateMiscSquare(column - floorOffset, row + floorOffset, (y * -1) + 0.5, scale, "barrels.png");
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row + scale, y * -1, scale, "wallBottom.png");
				}
			}
			// Create bottom walls.
			else if (y == -size)
			{
				if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column - floorOffset, row + scale * 2, y * -1, scale, "woodPile.png");
				}
				SpawnManager::getInstance()->generateMiscSquare(column, row + scale, y * -1, scale, "wallBottom.png");
			}
			// Create a left wall
			else if (x == 0)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset + scale / 2, y * -1, scale, "wallLeft.png");
				SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset, (y * -1) + 0.5, scale, "wallLeft.png");
			}
			// Create a right wall.
			else if (x == size)
			{
				float wallHorizontalOffset = scale;

				SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset + scale / 2, y * -1, scale, "wallRight.png");
				SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png");
			}
		}
	}

	SpawnManager::getInstance()->generateWorldItem(-5, -5, std::make_shared<WoodenLongbow>());

	setCameraFollow(SpawnManager::getInstance()->generatePlayerCharacter(20, 20));
}

void CharacterTestScene::setCameraFollow(std::shared_ptr<GameObject> toFollow)
{
	Camera::getActiveCamera()->getComponent<CameraFollow>()->setToFollow(toFollow);
}

void CharacterTestScene::onPause()
{
}

void CharacterTestScene::onEnd()
{

}

void CharacterTestScene::onUpdate(int ticks)
{
}