#pragma once

#ifndef _GAMESCREENLEVEL3_H
#define _GAMESCREENLEVEL3_H

#include "GameScreen.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "Character.h"
#include "GameObject.h"
#include "GameText.h"
#include "constants.h"

class Texture2D;

class Character;

class GameObject;

class GameScreenLevel3 : GameScreen
{
private:

	GameScreenManager* gameScreenManager;

	Texture2D* m_background_texture;

	Vector2D characterSpawnCoords;

	Character* m_character;

	Character* m_meleeAttacks[4];

	GameObject* m_exitDoor;
	GameObject* m_spikes;
	GameObject* m_button;
	GameObject* m_buttonBase;

	GameObject* m_moveOrb[5];
	GameObject* m_moveOrbRail[5];
	GameObject* m_railEndPoint[5];
	GameObject* m_dashOrb[5];

	GameObject* m_border[3];
	GameObject* m_floor[5];
	GameObject* m_leftWall[5];
	GameObject* m_rightWall[5];

	GameText* m_gameText[6];

	bool SetUpLevel();

	Vector2D m_characterPosition;

public:

	GameScreenLevel3(SDL_Renderer* renderer, GameScreenManager* gameScreen);
	~GameScreenLevel3();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void Inputs(SDL_Event e);

protected:

	bool m_isMoveOrbActive;
	bool m_moveOrbLeft;
	bool m_moveOrbRight;
};

#endif //_GAMESCREENLEVEL3_H
