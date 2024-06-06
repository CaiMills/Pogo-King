#pragma once

#ifndef _GAMESCREENMAINMENU_H
#define _GAMESCREENMAINMENU_H

#include "GameScreen.h"
#include "commons.h"
#include "GameScreenManager.h"
#include "GameText.h"
#include "GameObject.h"

class Texture2D;

class GameScreenMainMenu : GameScreen
{
private:

	GameScreenManager* gameScreenManager;

	Texture2D* m_background_texture;

	bool SetUpLevel();

	GameText* m_gameText[1];

	GameObject* m_title;

public:

	GameScreenMainMenu(SDL_Renderer* renderer, GameScreenManager* gameScreen);
	~GameScreenMainMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void Inputs(SDL_Event e);
};

#endif //_GAMESCREENMAINMENU_H

