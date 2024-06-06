#include "GameScreenLevel3.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "Character.h"
#include "GameObject.h"
#include "constants.h"


GameScreenLevel3::GameScreenLevel3(SDL_Renderer* renderer, GameScreenManager* gameScreen) : GameScreen(renderer)
{
	SetUpLevel();

	gameScreenManager = gameScreen;

	characterSpawnCoords.x = 32;
	characterSpawnCoords.y = 310;

	m_characterPosition = characterSpawnCoords;

	m_isMoveOrbActive = false;
	m_moveOrbLeft = false;
	m_moveOrbRight = false;
}

GameScreenLevel3::~GameScreenLevel3()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_character;
	m_character = nullptr;

	delete m_moveOrb[0];
	m_moveOrb[0] = nullptr;

	delete m_moveOrbRail[0];
	m_moveOrbRail[0] = nullptr;

	delete m_railEndPoint[0];
	m_railEndPoint[0] = nullptr;

	delete m_railEndPoint[1];
	m_railEndPoint[1] = nullptr;

	delete m_dashOrb[0];
	m_dashOrb[0] = nullptr;

	delete m_meleeAttacks[0];
	m_meleeAttacks[0] = nullptr;

	delete m_meleeAttacks[1];
	m_meleeAttacks[0] = nullptr;

	delete m_meleeAttacks[2];
	m_meleeAttacks[0] = nullptr;

	delete m_meleeAttacks[3];
	m_meleeAttacks[0] = nullptr;

	delete m_border[0];
	m_border[0] = nullptr;

	delete m_border[1];
	m_border[1] = nullptr;

	delete m_border[2];
	m_border[2] = nullptr;

	delete m_floor[0];
	m_floor[0] = nullptr;

	delete m_floor[1];
	m_floor[1] = nullptr;

	delete m_leftWall[0];
	m_leftWall[0] = nullptr;

	delete m_rightWall[0];
	m_rightWall[0] = nullptr;

	delete m_rightWall[1];
	m_rightWall[1] = nullptr;

	delete m_rightWall[2];
	m_rightWall[2] = nullptr;

	delete m_exitDoor;
	m_exitDoor = nullptr;

	delete m_spikes;
	m_spikes = nullptr;

	delete m_button;
	m_button = nullptr;

	delete m_buttonBase;
	m_buttonBase = nullptr;
}

bool GameScreenLevel3::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/background3.png"))
	{
		std::cout << " Failed to load background texture!" << std::endl;
		return false;
	}

	//sets up the environment
	m_floor[0] = new GameObject(m_renderer, "Images/floor2.png", Vector2D(0, 532));
	m_floor[1] = new GameObject(m_renderer, "Images/floor2.png", Vector2D(1024, 528));
	m_leftWall[0] = new GameObject(m_renderer, "Images/wall2.png", Vector2D(224, 564));
	m_rightWall[0] = new GameObject(m_renderer, "Images/wall2.png", Vector2D(1024, 560));
	m_rightWall[1] = new GameObject(m_renderer, "Images/wall2.png", Vector2D(1024, 16));
	m_rightWall[2] = new GameObject(m_renderer, "Images/movableDoor.png", Vector2D(1024, 268));

	//sets up game text
	m_gameText[0] = new GameText(m_renderer, "Fonts/arial.ttf", 20);
	m_gameText[1] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
	m_gameText[2] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
	m_gameText[3] = new GameText(m_renderer, "Fonts/arial.ttf", 50);

	//sets up player character
	m_character = new Character(m_renderer, "Images/player.png", Vector2D(32, 310));

	//sets up orb objects
	m_dashOrb[0] = new GameObject(m_renderer, "Images/dashOrb.png", Vector2D(850,250));
	m_moveOrbRail[0] = new GameObject(m_renderer, "Images/moveOrbRail.png", Vector2D(335, 502));
	m_railEndPoint[0] = new GameObject(m_renderer, "Images/railEndPoint.png", Vector2D(330, 500));
	m_railEndPoint[1] = new GameObject(m_renderer, "Images/railEndPoint.png", Vector2D(900, 500));
	m_moveOrb[0] = new GameObject(m_renderer, "Images/moveOrb.png", Vector2D(272, 470));

	//sets up the melee attack hitboxes (these are intentionally placed outside the map, so they can be moved in later)
	m_meleeAttacks[0] = new Character(m_renderer, "Images/meleeRight.png", Vector2D(9999, 9999));
	m_meleeAttacks[1] = new Character(m_renderer, "Images/meleeLeft.png", Vector2D(9999, 9999));
	m_meleeAttacks[2] = new Character(m_renderer, "Images/meleeUp.png", Vector2D(9999, 9999));
	m_meleeAttacks[3] = new Character(m_renderer, "Images/meleeDown.png", Vector2D(9999, 9999));

	//sets up other objects
	m_exitDoor = new GameObject(m_renderer, "Images/goldenCarrot.png", Vector2D(1180, 400));
	m_spikes = new GameObject(m_renderer, "Images/spikes.png", Vector2D(272, 688));
	m_button = new GameObject(m_renderer, "Images/button.png", Vector2D(962, 100));
	m_buttonBase = new GameObject(m_renderer, "Images/buttonBase.png", Vector2D(992, 100));

	//sets up borders
	m_border[0] = new GameObject(m_renderer, "Images/floorBorder.png", Vector2D(0, 0));
	m_border[1] = new GameObject(m_renderer, "Images/wallBorder.png", Vector2D(0, 0));
	m_border[2] = new GameObject(m_renderer, "Images/wallBorder.png", Vector2D(1264, 0));
}

void GameScreenLevel3::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//render environment
	m_floor[0]->Render();
	m_floor[1]->Render();
	m_leftWall[0]->Render();
	m_rightWall[0]->Render();
	m_rightWall[1]->Render();
	m_rightWall[2]->Render();

	//controls the color the text is rendered at
	m_gameText[0]->SetColor(SDL_Color{ 255, 238, 0, 0 });
	m_gameText[1]->SetColor(SDL_Color{ 255, 165, 0, 0 });
	m_gameText[2]->SetColor(SDL_Color{ 3, 252, 36, 0 });
	m_gameText[3]->SetColor(SDL_Color{ 255, 165, 0, 0 });

	//controls what the text says and its world position
	m_gameText[0]->RenderAt("LEVEL 3", 20, 20);
	m_gameText[1]->RenderAt("Hit the ", 475, 75);
	m_gameText[2]->RenderAt("GREEN ", 630, 75);
	m_gameText[3]->RenderAt("orbs and they will move", 375, 125);

	//render character
	m_character->Render();

	//render orb objects
	m_dashOrb[0]->Render();
	m_moveOrbRail[0]->Render();
	m_railEndPoint[0]->Render();
	m_railEndPoint[1]->Render();
	m_moveOrb[0]->Render();

	//render melee attacks
	m_meleeAttacks[0]->Render();
	m_meleeAttacks[1]->Render();
	m_meleeAttacks[2]->Render();
	m_meleeAttacks[3]->Render();

	//render other objects
	m_exitDoor->Render();
	m_spikes->Render();
	m_button->Render();
	m_buttonBase->Render();

	//render borders
	m_border[0]->Render();
	m_border[1]->Render();
	m_border[2]->Render();
}

void GameScreenLevel3::Update(float deltaTime, SDL_Event e)
{
	//update character
	m_character->Update(deltaTime, e);
	m_characterPosition = m_character->GetPosition();

	Inputs(e);

	if (m_moveOrbRight == true)
	{
		Vector2D m_position = m_moveOrb[0]->GetPosition();
		m_position.x += (deltaTime * 200);

		m_moveOrb[0]->SetPosition(m_position);
	}
	if (m_moveOrbLeft == true)
	{
		Vector2D m_position = m_moveOrb[0]->GetPosition();
		m_position.x -= (deltaTime * 200);

		m_moveOrb[0]->SetPosition(m_position); 
	}

#pragma region Orb Collisions

	if (Collisions::Instance()->Box(m_meleeAttacks[0]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Right");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[1]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Left");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[2]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Up");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[3]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Down");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[0]->GetCollisionBox(), m_moveOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Left", 900);
		m_isMoveOrbActive = true;
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[1]->GetCollisionBox(), m_moveOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Right", 900);
		m_isMoveOrbActive = true;
	}


	if (Collisions::Instance()->Box(m_meleeAttacks[2]->GetCollisionBox(), m_moveOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Down", 900);
		m_isMoveOrbActive = true;
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[3]->GetCollisionBox(), m_moveOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Up", 900);
		m_isMoveOrbActive = true;
	}

	if (m_isMoveOrbActive == true)
	{
		if (Collisions::Instance()->Box(m_moveOrb[0]->GetCollisionBox(), m_railEndPoint[0]->GetCollisionBox()))
		{
			m_moveOrbRight = true;
			m_moveOrbLeft = false;
		}

		if (Collisions::Instance()->Box(m_moveOrb[0]->GetCollisionBox(), m_railEndPoint[1]->GetCollisionBox()))
		{
			m_moveOrbRight = false;
			m_moveOrbLeft = true;
		}
	}

#pragma endregion

#pragma region Floor Collisions

	//floor collisions
	bool isGrounded = false;

	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_floor[0]->GetCollisionBox()))
	{
		isGrounded = true;
	}
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_floor[1]->GetCollisionBox()))
	{
		isGrounded = true;
	}

	m_character->GroundCheck(isGrounded);

#pragma endregion

#pragma region Wall Collisions

	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_leftWall[0]->GetCollisionBox()))
	{
		m_character->MoveLeft(deltaTime);
	}
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_rightWall[0]->GetCollisionBox()))
	{
		m_character->MoveRight(deltaTime);
	}
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_rightWall[1]->GetCollisionBox()))
	{
		m_character->MoveRight(deltaTime);
	}
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_rightWall[2]->GetCollisionBox()))
	{
		m_character->MoveRight(deltaTime);
	}
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_border[1]->GetCollisionBox()))
	{
		m_character->MoveRight(deltaTime);
	}
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_border[2]->GetCollisionBox()))
	{
		m_character->MoveLeft(deltaTime);
	}

#pragma endregion

#pragma region Other Collisions

	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_spikes->GetCollisionBox()))
	{
		m_character->SetPosition(characterSpawnCoords);
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[0]->GetCollisionBox(), m_button->GetCollisionBox()))
	{
		Vector2D outOfBounds;
		outOfBounds.x = 9999.9f;
		outOfBounds.y = 9999.9f;

		m_button->SetPosition(outOfBounds);
		m_rightWall[2]->SetPosition(outOfBounds);
	}

	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_exitDoor->GetCollisionBox()))
	{
		gameScreenManager->ChangeScreen(SCREEN_WIN);
	}

#pragma endregion

}

void GameScreenLevel3::Inputs(SDL_Event e)
{
	//Keyboard inputs
	switch (e.type)
	{
	case SDL_KEYDOWN: //this runs the functions when the keys are down
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT: //right Melee attack
			m_meleeAttacks[0]->Melee(m_meleeAttacks[0], m_characterPosition, "Right");
			break;

		case SDLK_LEFT: //left Melee attack
			m_meleeAttacks[1]->Melee(m_meleeAttacks[1], m_characterPosition, "Left");
			break;

		case SDLK_UP: //up Melee attack
			m_meleeAttacks[2]->Melee(m_meleeAttacks[2], m_characterPosition, "Up");
			break;

		case SDLK_DOWN: //down Melee attack
			m_meleeAttacks[3]->Melee(m_meleeAttacks[3], m_characterPosition, "Down");
			break;
		}
		break;
	case SDL_JOYBUTTONDOWN: //this runs the functions when the buttons are down
		switch (e.jbutton.button)
		{
		case 9: //right Melee attack
			m_meleeAttacks[0]->Melee(m_meleeAttacks[0], m_characterPosition, "Right");
			break;

		case 7: //left Melee attack
			m_meleeAttacks[1]->Melee(m_meleeAttacks[1], m_characterPosition, "Left");
			break;

		case 2: //up Melee attack
			m_meleeAttacks[2]->Melee(m_meleeAttacks[2], m_characterPosition, "Up");
			break;

		case 4: //down Melee attack
			m_meleeAttacks[3]->Melee(m_meleeAttacks[3], m_characterPosition, "Down");
			break;
			break;
		}
	}
}