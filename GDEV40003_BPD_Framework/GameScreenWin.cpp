#include "GameScreenWin.h"
#include <iostream>
#include "Texture2D.h"

GameScreenWin::GameScreenWin(SDL_Renderer* renderer, GameScreenManager* gameScreen) : GameScreen(renderer)
{
	SetUpLevel();

	gameScreenManager = gameScreen;
}

GameScreenWin::~GameScreenWin()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

bool GameScreenWin::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/winBackground.png"))
	{
		std::cout << " Failed to load background texture!" << std::endl;
		return false;
	}

	//sets up game text
	m_gameText[0] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
}

void GameScreenWin::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//controls the color the text is rendered at
	m_gameText[0]->SetColor(SDL_Color{ 0, 239, 225, 0 });

	//controls what the text says and its world position
	m_gameText[0]->RenderAt("PRESS START OR ESCAPE TO RETURN TO MENU", 55, 575);
}

void GameScreenWin::Update(float deltaTime, SDL_Event e)
{
	Inputs(e);
}

void GameScreenWin::Inputs(SDL_Event e)
{
	//Keyboard inputs
	switch (e.type)
	{
	case SDL_KEYDOWN: //this runs the functions when the keys are down
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			gameScreenManager->ChangeScreen(SCREEN_MAINMENU);
			break;
		}
		break;

	case SDL_JOYBUTTONDOWN: //this runs the functions when the buttons are down
		switch (e.jbutton.button)
		{
		case 3:
			gameScreenManager->ChangeScreen(SCREEN_MAINMENU);
			break;
		}
		break;
	}
}