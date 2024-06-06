#include "GameScreenMainMenu.h"
#include <iostream>
#include "Texture2D.h"

GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer, GameScreenManager* gameScreen) : GameScreen(renderer)
{
	SetUpLevel();

	gameScreenManager = gameScreen;
}

GameScreenMainMenu::~GameScreenMainMenu()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_title;
	m_title = nullptr;
}

bool GameScreenMainMenu::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/mainMenuBackground.png"))
	{
		std::cout << " Failed to load background texture!" << std::endl;
		return false;
	}

	//sets up game objects
	m_title = new GameObject(m_renderer, "Images/title.png", Vector2D(275, 35));

	//sets up game text
	m_gameText[0] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
}

void GameScreenMainMenu::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//render other objects
	m_title->Render();

	//controls the color the text is rendered at
	m_gameText[0]->SetColor(SDL_Color{ 255, 238, 0, 0 });

	//controls what the text says and its world position
	m_gameText[0]->RenderAt("PRESS START OR SPACE TO PLAY", 230, 575);
}

void GameScreenMainMenu::Update(float deltaTime, SDL_Event e)
{
	Inputs(e);
}

void GameScreenMainMenu::Inputs(SDL_Event e)
{
	//Keyboard inputs
	switch (e.type)
	{
	case SDL_KEYDOWN: //this runs the functions when the keys are down
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE: 
			gameScreenManager->ChangeScreen(SCREEN_CONTROLS);
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