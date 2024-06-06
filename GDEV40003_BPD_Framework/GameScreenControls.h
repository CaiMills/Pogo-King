#pragma once

#ifndef _GAMESCREENCONTROLS_H
#define _GAMESCREENCONTROLS_H

#include "GameScreen.h"
#include "commons.h"
#include "GameScreenManager.h"

class Texture2D;

class GameScreenControls : GameScreen
{
private:

	GameScreenManager* gameScreenManager;

	Texture2D* m_background_texture;

	bool SetUpLevel();

public:

	GameScreenControls(SDL_Renderer* renderer, GameScreenManager* gameScreen);
	~GameScreenControls();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void Inputs(SDL_Event e);
};

#endif //_GAMESCREENCONTROLS_H

