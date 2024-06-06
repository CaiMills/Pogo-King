#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "GameObject.h"
#include "GameScreenManager.h"

class Collision;

class Character : public GameObject
{
private:
	
	FACING m_facingDirection;

public:

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void Jump(float deltaTime);

	void Inputs(SDL_Event e);

	void GroundCheck(bool isGrounded);
	void Gravity(float deltaTime);

	static Uint32 MeleeAttackCallback(Uint32 interval, void* param);

	bool Melee(GameObject* meleeAttack, Vector2D characterPos, string direction);
	void Bounce(float deltaTime, string direction, float bounceStrength);
	void Dash(float deltaTime, string direction);

protected:

	bool m_moving_left;
	bool m_moving_right;
	bool m_isJumping;
	bool m_isGrounded;

	float m_gravity;
	float m_jumpPower;
	float m_maxJumpHeight;

	float m_bounceStrength;
	float m_bounceDistance;
	float m_dashStrength;
	float m_dashDistance;
	
	Vector2D m_velocity;

	bool m_isMeleeAttacking = false;
	SDL_TimerID attackTimerID;
	Uint32 attackTimer;
	Vector2D m_oldMeleeAttackPosition;
	GameObject* m_currentMeleeAttack;
};

#endif //_CHARACTER_H