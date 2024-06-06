#include "Melee.h"
#include "Texture2D.h"

Melee::Melee(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : GameObject(renderer, imagePath, start_position)
{
	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << " Failed to load texture from image path!" << std::endl;
	}

	//this currently is just a guess on the correct radius, when given the chance, make it so that it can get the radius from the texture itself, this requires a variable for both height and width
	m_collisionRadius = 30.0f;
}

Melee::~Melee()
{
	m_renderer = nullptr;
}

void Melee::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Melee::Update(float deltaTime, SDL_Event e)
{

}

void Melee::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Melee::GetPosition()
{
	return m_position;
}

float Melee::GetCollisionRadius()
{
	return m_collisionRadius;
}