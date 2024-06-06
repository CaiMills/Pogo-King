#pragma once

#ifndef _GAMESCREENWIN_H
#define _GAMESCREENWIN_H

#include "GameScreen.h"
#include "commons.h"
#include "GameScreenManager.h"
#include "GameText.h"

class Texture2D;

class GameScreenWin : GameScreen
{
private:

	GameScreenManager* gameScreenManager;

	Texture2D* m_background_texture;

	bool SetUpLevel();

	GameText* m_gameText[2];

public:

	GameScreenWin(SDL_Renderer* renderer, GameScreenManager* gameScreen);
	~GameScreenWin();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void Inputs(SDL_Event e);
};

#endif //_GAMESCREENWIN_H

