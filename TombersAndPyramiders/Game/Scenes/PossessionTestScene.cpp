#include "PossessionTestScene.h"
#include <iostream>
#include <vector>
#include "SpawnManager.h"
#include "Camera.h"
#include "GameManager.h"

/*
New Z Rule:

-10	Floor
-1	Behind-Default
0	Default
1	Above-Default
10	Ceiling

*/

PossessionTestScene::PossessionTestScene()
{
}

void PossessionTestScene::onStart()
{
	GameManager::getInstance()->resizeQuadTree(0, 0, 200, 100);
	for (int x = -20; x < 21; x += 10) {
		auto bg = SpawnManager::getInstance()->generateMiscSquare(x, 0, 0, 10, "stoneTile.png", false);
		bg->getTransform()->setZ(-10);
	}
	for (int x = -20; x < 21; x += 10) {
		auto bg = SpawnManager::getInstance()->generateMiscSquare(x, 0, 0, 10, "stoneTile.png", false);
		bg->getTransform()->setZ(-10);
	}
	for (int x = -21; x < 21; x++) {
		SpawnManager::getInstance()->generateMiscSquare(x, 5, 0, 1, "stoneTile.png", true, 1.0f);
		SpawnManager::getInstance()->generateMiscSquare(x, -5, 0, 1, "stoneTile.png", true, 1.0f);
	}
	auto ghostCharacter = SpawnManager::getInstance()->generateGhost(0, 0);
	SpawnManager::getInstance()->generateBoulder(5, 0);
	SpawnManager::getInstance()->generateAiCharacter(-10, 0);
	SpawnManager::getInstance()->generateAiCharacter(15, 5);
	Camera::getActiveCamera()->addComponent<CameraFollow>((GameObject*)Camera::getActiveCamera().get())->setToFollow(ghostCharacter);
}

void PossessionTestScene::onPause()
{
}

void PossessionTestScene::onEnd()
{

}

void PossessionTestScene::onUpdate(int ticks)
{
}