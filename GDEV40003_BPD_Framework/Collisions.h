#pragma once
#include "commons.h"

class Character;

class GameObject;

class Collisions
{
private:

	Collisions();

	static Collisions* m_instance;

public:

	~Collisions();

	static Collisions* Instance();

	bool Circle(GameObject* a, GameObject* b);
	bool Box(Rect2D rect1, Rect2D rect2);
};

