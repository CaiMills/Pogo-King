#include "GameScreenControls.h"
#include <iostream>
#include "Texture2D.h"

GameScreenControls::GameScreenControls(SDL_Renderer* renderer, GameScreenManager* gameScreen) : GameScreen(renderer)
{
	SetUpLevel();

	gameScreenManager = gameScreen;
}

GameScreenControls::~GameScreenControls()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

bool GameScreenControls::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/tutorialImage.png"))
	{
		std::cout << " Failed to load background texture!" << std::endl;
		return false;
	}
}

void GameScreenControls::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenControls::Update(float deltaTime, SDL_Event e)
{
	Inputs(e);
}

void GameScreenControls::Inputs(SDL_Event e)
{
	//Keyboard inputs
	switch (e.type)
	{
	case SDL_KEYDOWN: //this runs the functions when the keys are down
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gameScreenManager->ChangeScreen(SCREEN_MISSION);
			break;
		}
		break;

	case SDL_JOYBUTTONDOWN: //this runs the functions when the buttons are down
		switch (e.jbutton.button)
		{
		case 3:
			gameScreenManager->ChangeScreen(SCREEN_MISSION);
			break;
		}
		break;
	}
}