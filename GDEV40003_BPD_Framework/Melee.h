#pragma once

#ifndef _MELEE_H
#define _MELEE_H

#include "Character.h"

class Melee : public GameObject
{
protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	float m_collisionRadius;

public:

	Melee(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~Melee();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

};

#endif //_MELEE_H