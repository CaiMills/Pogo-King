#pragma once

#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "SDL.h"
#include "commons.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

class Texture2D;

class GameObject
{
protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	float m_collisionRadius;

public:

	GameObject(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~GameObject();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

 	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
};

#endif // _GAMEOBJECT_H