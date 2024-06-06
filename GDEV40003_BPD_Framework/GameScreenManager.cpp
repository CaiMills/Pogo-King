#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenMainMenu.h"
#include "GameScreenControls.h"
#include "GameScreenMission.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenLevel3.h"
#include "GameScreenWin.h"
#include <iostream>

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;

	m_current_screen = nullptr;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	GameScreenMainMenu* MainMenu;
	GameScreenControls* Controls;
	GameScreenMission* Mission;
	GameScreenLevel1* Level1;
	GameScreenLevel2* Level2;
	GameScreenLevel3* Level3;
	GameScreenWin* Win;

	switch (new_screen)
	{
	case SCREEN_MAINMENU:
		MainMenu = new GameScreenMainMenu(m_renderer, this);
		m_current_screen = (GameScreen*)MainMenu;
		MainMenu = nullptr;
	break;
	default: ;
	case SCREEN_CONTROLS:
		Controls = new GameScreenControls(m_renderer, this);
		m_current_screen = (GameScreen*)Controls;
		Controls = nullptr;
		break;
	case SCREEN_MISSION:
		Mission = new GameScreenMission(m_renderer, this);
		m_current_screen = (GameScreen*)Mission;
		Mission = nullptr;
		break;
	case SCREEN_LEVEL1:
		Level1 = new GameScreenLevel1(m_renderer, this);
		m_current_screen = (GameScreen*)Level1;
		Level1 = nullptr;
	break;
	case SCREEN_LEVEL2:
		Level2 = new GameScreenLevel2(m_renderer, this);
		m_current_screen = (GameScreen*)Level2;
		Level2 = nullptr;
	break;
	case SCREEN_LEVEL3:
		Level3 = new GameScreenLevel3(m_renderer, this);
		m_current_screen = (GameScreen*)Level3;
		Level3 = nullptr;
	break;
	case SCREEN_WIN:
		Win = new GameScreenWin(m_renderer, this);
		m_current_screen = (GameScreen*)Win;
		Win = nullptr;
	break;
	}
}

