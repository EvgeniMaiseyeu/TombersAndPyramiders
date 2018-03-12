#pragma once

#include <string>
#include "GameObject.h"
#include "Transform.h"
#include <iostream>

//Senders transform message and extra commands

class Sender : public Component
{
private:
	std::string m_id;

public:
	Sender(GameObject* gameObject, std::string ID);
	void sendCreate();
	void sendDestroy();
	void sendUpdate();
	void sendAttack();
	void sendNetworkMessage(std::string messageKey, std::map<std::string, std::string> payload);
	void spawnPlayers(float p1x, float p1y, float p2x, float p2y);
	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};
	~Sender();
};