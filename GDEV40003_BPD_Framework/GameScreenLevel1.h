#pragma once

#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "commons.h"
#include "Character.h"
#include "GameText.h"
#include "GameScreenManager.h"

class Texture2D;

class Character;

class GameObject;

class GameScreenLevel1 : GameScreen
{
private:

	GameScreenManager* gameScreenManager;

	Texture2D* m_background_texture;

	Vector2D characterSpawnCoords;

	Character* m_character;

	Character* m_meleeAttacks[4];

	GameObject* m_bounceOrb[5];

	GameObject* m_exitDoor;
	GameObject* m_spikes;

	GameObject* m_border[3];
	GameObject* m_floor[5];
	GameObject* m_leftWall[5];
	GameObject* m_rightWall[5];
	
	GameText* m_gameText[5];

	bool SetUpLevel();

	Vector2D m_characterPosition;

public:

	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* gameScreen);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void Inputs(SDL_Event e);
};

#endif //_GAMESCREENLEVEL1_H
