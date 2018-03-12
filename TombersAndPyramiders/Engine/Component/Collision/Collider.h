#pragma once

#include "GameObject.h"
#include "Component.h"

class Collider : public Component
{
private:
	GameObject* m_colliderObj;
	Transform* m_transform;
	//float m_radius;
	bool m_collision;
	std::vector<GameObject*> m_colliders;
	bool m_disabled;
	bool m_isTrigger = false;
public:
	Collider(GameObject* gameObject/*, float radius*/);
	bool doesCollide(GameObject* other);
	//float getRadius();
	//void setRadius(float radius);

	bool collisionDetected();
	void setCollision(bool collision);

	void setDisabled(bool value);
	bool getDisabled();
	void setIsTrigger(bool isNowTrigger);
	bool isTrigger();

	GameObject* getColliderObj();
	void setColliderObj(GameObject* collider);
	void addCollision(GameObject* collider);
	void clearColliders();
	std::vector<GameObject*> getColliders();

	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};

	~Collider();
};