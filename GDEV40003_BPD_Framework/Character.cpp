#include "Character.h"
#include "Texture2D.h"
#include "constants.h"
#include "Collisions.h"
#include "SDL_timer.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer, imagePath, startPosition)
{
	m_moving_left = false;
	m_moving_right = false;
	m_isJumping = false;
	m_isGrounded = false;

	m_gravity = 0;
	m_jumpPower = 500.0f;
	m_maxJumpHeight = 0.0f;

	m_bounceStrength = 0.0f;
	m_bounceDistance = 0.0f;
	m_dashDistance = 0.0f;
	m_dashStrength = 0.0f;

	m_velocity.y = 0.0f;
	m_velocity.x = 0.0f;

	attackTimerID = NULL;
	attackTimer = NULL;

	m_oldMeleeAttackPosition.y = 9999.0f;
	m_oldMeleeAttackPosition.x = 9999.0f;
	m_currentMeleeAttack = nullptr;

	m_facingDirection = FACING_LEFT;
}

Character::~Character()
{

}

void Character::Render()
{
	if (m_facingDirection == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	Gravity(deltaTime); 

	GroundCheck(m_isGrounded);

	Inputs(e);

	if (m_moving_left == true)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right == true)
	{
		MoveRight(deltaTime);
	}

	if (m_isJumping == true)
	{
		Jump(deltaTime);
	}

	// Update melee attack state
	//if an attack is still happening AND it has been more than x milliseconds
	if (m_isMeleeAttacking == true && SDL_GetTicks() >= attackTimer) 
	{
		m_isMeleeAttacking = false;

		m_currentMeleeAttack->SetPosition(m_oldMeleeAttackPosition);
		SDL_RemoveTimer(attackTimerID);
		attackTimerID = 0;
	}
}

void Character::Inputs(SDL_Event e)
{
	//Keyboard inputs
	switch (e.type)
	{
	case SDL_KEYDOWN: //this runs the functions when the keys are down
		switch (e.key.keysym.sym)
		{
		case SDLK_a: //left
			m_moving_left = true;
			m_facingDirection = FACING_LEFT;
			break;

		case SDLK_d: //right
			m_moving_right = true;
			m_facingDirection = FACING_RIGHT;
			break;

		case SDLK_SPACE: //jump
			if (m_isJumping == false && m_isGrounded == true)
			{
				m_isJumping = true;
				break;
			}

		case SDLK_w: //jump alternative
			if (m_isJumping == false && m_isGrounded == true)
			{
				m_isJumping = true;
				break;
			}
		}
		break;

	case SDL_KEYUP: //this runs the functions when the keys are up
		switch (e.key.keysym.sym)
		{
		case SDLK_a: //left
			m_moving_left = false;
			break;

		case SDLK_d: //right
			m_moving_right = false;
			break;

		break;

		case SDL_JOYBUTTONDOWN: //this runs the functions when the buttons are down
			switch (e.jbutton.button)
			{
			case 14: //left
				m_moving_left = true;
				m_facingDirection = FACING_LEFT;
				break;

			case 15: //right
				m_moving_right = true;
				m_facingDirection = FACING_RIGHT;
				break;

			case 13: //jump
				if (m_isJumping == false && m_isGrounded == true)
				{
					m_isJumping = true;
					break;
				}

			case 1: //jump alternative
				if (m_isJumping == false && m_isGrounded == true)
				{
					m_isJumping = true;
					break;
				}
			}
			break;

		case SDL_JOYBUTTONUP: //this runs the functions when the buttons are up
			switch (e.jbutton.button)
			{
			case 14: //left
				m_moving_left = false;
				break;

			case 15: //right
				m_moving_right = false;
				break;
			break;
			}
		}
	}
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= (deltaTime * MOVEMENTSPEED);
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += (deltaTime * MOVEMENTSPEED);
}

void Character::Jump(float deltaTime)
{
	m_maxJumpHeight == m_position.y + 600.0f;

	m_velocity.y = -m_jumpPower;

	if (m_position.y >= m_maxJumpHeight)
	{
		m_isJumping = false;
		m_maxJumpHeight = 0.0f;
	}
}

void Character::GroundCheck(bool isGrounded)
{
	//this function is only to check for if the player is colliding with ground
	m_isGrounded = isGrounded;
}

void Character::Gravity(float deltaTime)
{
	if (m_isGrounded == true)
	{
		m_gravity = 0.0f;
	}

	if (m_isGrounded == false)
	{
		m_gravity = 1000.0f;
		m_velocity.y += (m_gravity * deltaTime);
		m_position.y += m_velocity.y * deltaTime;
	}
}

Uint32 Character::MeleeAttackCallback(Uint32 interval, void* param)
{
	//as this function is technically is out of the character class due to SDL timer system being weird, i need a reference of the character to call certain functions and bools
	Character* characterRef = static_cast<Character*>(param);

	if (characterRef->m_currentMeleeAttack)
	{
		characterRef->m_isMeleeAttacking = false;
		characterRef->m_currentMeleeAttack->SetPosition(characterRef->m_oldMeleeAttackPosition);
	}

	return 0;
 }


bool Character::Melee(GameObject* meleeAttack, Vector2D characterPos, string direction)
{
	//this prevents the player from spamming the attack button
	if (m_isMeleeAttacking == true)
	{
		return false;
	}
	m_isMeleeAttacking = true;

	m_currentMeleeAttack = meleeAttack;

	//creates the timer
	attackTimerID = SDL_AddTimer(100, MeleeAttackCallback, this);

	//this keeps track of how much time its been, as this variable holds x milliseconds as well as the current ticks, so if I later compare the current ticks with attackTimer, if the current ticks
	//is larger than the attackTimer variable, then that means x milliseconds has passed
	attackTimer = SDL_GetTicks() + 100;

	Vector2D offset;
	offset.x = 0.0f;
	offset.y = 0.0f;

	if (direction == "Right")
	{
		offset.x = 30;
	}
	if (direction == "Left")
	{
		offset.x = -100;
	}
	if (direction == "Up")
	{
		offset.x = -20;
		offset.y = -60;
	}
	if (direction == "Down")
	{
		offset.x = -20;
		offset.y = 30;
	}

	//this accounts for the position offset, so that it doesnt spawn directly on the player
	characterPos.x = characterPos.x + offset.x;
	characterPos.y = characterPos.y + offset.y;

	//sets the meleeAttack's position to be the same as the character + offset
	meleeAttack->SetPosition(characterPos);

	return true;
}

void Character::Bounce(float deltaTime, string direction, float bounceStrength)
{
	m_bounceStrength = bounceStrength;

	if (direction == "Right")
	{
		m_bounceDistance == m_position.x + 800;

		m_velocity.x = m_bounceStrength;
		m_position.x += m_velocity.x * deltaTime;

		if (m_position.x >= m_bounceDistance)
		{
			m_velocity.x = 0.0f;
			m_bounceDistance = 0.0f;
		}
	}
	if (direction == "Left")
	{
		m_bounceDistance == m_position.x + 800;

		m_velocity.x = -m_bounceStrength;
		m_position.x += m_velocity.x * deltaTime;

		if (m_position.x >= m_bounceDistance)
		{
			m_velocity.x = 0.0f;
			m_bounceDistance = 0.0f;
		}
	}
	if (direction == "Up")
	{
		m_bounceDistance == m_position.y + 800;

		m_velocity.y = -m_bounceStrength;
		m_position.y += m_velocity.y * deltaTime;

		if (m_position.y >= m_bounceDistance)
		{
			m_velocity.y = 0.0f;
			m_bounceDistance = 0.0f;
		}
	}
	if (direction == "Down")
	{
		m_bounceDistance == m_position.y - 800;

		m_velocity.y = m_bounceStrength;
		m_position.y += m_velocity.y * deltaTime;

		if (m_position.y >= m_bounceDistance)
		{
			m_velocity.y = 0.0f;
			m_bounceDistance = 0.0f;
		}
	}
}

void Character::Dash(float deltaTime, string direction)
{
	m_dashStrength = 3000.0f;

	if (direction == "Right")
	{
		m_dashDistance == m_position.x + 2000;

		m_velocity.x = m_dashStrength;
		m_position.x += m_velocity.x * deltaTime;

		if (m_position.x >= m_dashDistance)
		{
			m_velocity.x = 0.0f;
			m_dashDistance = 0.0f;
		}
	}
	if (direction == "Left")
	{
		m_dashDistance == m_position.x + 2000;

		m_velocity.x = -m_dashStrength;
		m_position.x += m_velocity.x * deltaTime;

		if (m_position.x >= m_dashDistance)
		{
			m_velocity.x = 0.0f;
			m_dashDistance = 0.0f;
		}
	}
	if (direction == "Up")
	{
		m_dashDistance == m_position.y + 2000;

		m_velocity.y = -m_dashStrength;
		m_position.y += m_velocity.y * deltaTime;

		if (m_position.y >= m_dashDistance)
		{
			m_velocity.y = 0.0f;
			m_dashDistance = 0.0f;
		}
	}
	if (direction == "Down")
	{
		m_dashDistance == m_position.y - 2000;

		m_velocity.y = m_dashStrength;
		m_position.y += m_velocity.y * deltaTime;

		if (m_position.y >= m_dashDistance)
		{
			m_velocity.y = 0.0f;
			m_dashDistance = 0.0f; 
		}
	}
}