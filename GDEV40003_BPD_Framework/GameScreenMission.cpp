#include "GameScreenMission.h"
#include <iostream>
#include "Texture2D.h"

GameScreenMission::GameScreenMission(SDL_Renderer* renderer, GameScreenManager* gameScreen) : GameScreen(renderer)
{
	SetUpLevel();

	gameScreenManager = gameScreen;
}

GameScreenMission::~GameScreenMission()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

bool GameScreenMission::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/background5.png"))
	{
		std::cout << " Failed to load background texture!" << std::endl;
		return false;
	}

	m_gameText[0] = new GameText(m_renderer, "Fonts/arial.ttf", 75);
}

void GameScreenMission::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//controls the color the text is rendered at
	m_gameText[0]->SetColor(SDL_Color{ 255, 238, 0, 0 });

	//controls what the text says and its world position
	m_gameText[0]->RenderAt("GOAL: Get the Golden Carrot", 160, 320);
}

void GameScreenMission::Update(float deltaTime, SDL_Event e)
{
	Inputs(e);
}

void GameScreenMission::Inputs(SDL_Event e)
{
	//Keyboard inputs
	switch (e.type)
	{
	case SDL_KEYDOWN: //this runs the functions when the keys are down
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
			break;
		}
		break;

	case SDL_JOYBUTTONDOWN: //this runs the functions when the buttons are down
		switch (e.jbutton.button)
		{
		case 3:
			gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
			break;
		}
		break;
	}
}
