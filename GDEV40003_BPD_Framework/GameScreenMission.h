#pragma once

#ifndef _GAMESCREENMISSION_H
#define _GAMESCREENMISSION_H

#include "GameScreen.h"
#include "commons.h"
#include "GameScreenManager.h"
#include "GameText.h"

class Texture2D;

class GameScreenMission : GameScreen
{
private:

	GameScreenManager* gameScreenManager;

	Texture2D* m_background_texture;

	GameText* m_gameText[5];

	bool SetUpLevel();

public:

	GameScreenMission(SDL_Renderer* renderer, GameScreenManager* gameScreen);
	~GameScreenMission();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void Inputs(SDL_Event e);
};

#endif //_GAMESCREENMISSION_H
