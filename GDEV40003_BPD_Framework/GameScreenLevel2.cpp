#include "GameScreenLevel2.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "Character.h"
#include "GameObject.h"
#include "constants.h"


GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, GameScreenManager* gameScreen) : GameScreen(renderer)
{
	SetUpLevel();

	gameScreenManager = gameScreen;

	characterSpawnCoords.x = 32;
	characterSpawnCoords.y = 310;

	m_characterPosition = characterSpawnCoords;
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_character;
	m_character = nullptr;

	delete m_bounceOrb[0];
	m_bounceOrb[0] = nullptr;

	delete m_dashOrb[0];
	m_dashOrb[0] = nullptr;

	delete m_dashOrb[1];
	m_dashOrb[1] = nullptr;

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
	m_leftWall[2] = nullptr;

	delete m_exitDoor;
	m_exitDoor = nullptr;

	delete m_spikes;
	m_spikes = nullptr;
}

bool GameScreenLevel2::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/background2.png"))
	{
		std::cout << " Failed to load background texture!" << std::endl;
		return false;
	}

	//sets up the environment
	m_floor[0] = new GameObject(m_renderer, "Images/floor2.png", Vector2D(0, 432));
	m_floor[1] = new GameObject(m_renderer, "Images/floor2.png", Vector2D(1024, 328));
	m_leftWall[0] = new GameObject(m_renderer, "Images/wall2.png", Vector2D(224, 464));
	m_rightWall[0] = new GameObject(m_renderer, "Images/wall2.png", Vector2D(1024, 464));
	m_rightWall[1] = new GameObject(m_renderer, "Images/wall2.png", Vector2D(1024, 360));
	
	//sets up game text
	m_gameText[0] = new GameText(m_renderer, "Fonts/arial.ttf", 20);
	m_gameText[1] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
	m_gameText[2] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
	m_gameText[3] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
	m_gameText[4] = new GameText(m_renderer, "Fonts/arial.ttf", 50);
	m_gameText[5] = new GameText(m_renderer, "Fonts/arial.ttf", 50);

	//sets up player character
	m_character = new Character(m_renderer, "Images/player.png", Vector2D(32, 310));

	//sets up orb objects
	m_bounceOrb[0] = new GameObject(m_renderer, "Images/bounceOrb.png", Vector2D(600, 550));
	m_dashOrb[0] = new GameObject(m_renderer, "Images/dashOrb.png", Vector2D(600, 300));
	m_dashOrb[1] = new GameObject(m_renderer, "Images/dashOrb.png", Vector2D(750, 180));

	//sets up the melee attack hitboxes (these are intentionally placed outside the map, so they can be moved in later)
	m_meleeAttacks[0] = new Character(m_renderer, "Images/meleeRight.png", Vector2D(9999, 9999));
	m_meleeAttacks[1] = new Character(m_renderer, "Images/meleeLeft.png", Vector2D(9999, 9999));
	m_meleeAttacks[2] = new Character(m_renderer, "Images/meleeUp.png", Vector2D(9999, 9999));
	m_meleeAttacks[3] = new Character(m_renderer, "Images/meleeDown.png", Vector2D(9999, 9999));

	//sets up other objects
	m_exitDoor = new GameObject(m_renderer, "Images/exitDoor.png", Vector2D(1100, 200));
	m_spikes = new GameObject(m_renderer, "Images/spikes.png", Vector2D(272, 688));

	//sets up borders
	m_border[0] = new GameObject(m_renderer, "Images/floorBorder.png", Vector2D(0, 0));
	m_border[1] = new GameObject(m_renderer, "Images/wallBorder.png", Vector2D(0, 0));
	m_border[2] = new GameObject(m_renderer, "Images/wallBorder.png", Vector2D(1264, 0));
}

void GameScreenLevel2::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//render environment
	m_floor[0]->Render();
	m_floor[1]->Render();
	m_leftWall[0]->Render();
	m_rightWall[0]->Render();
	m_rightWall[1]->Render();

	//controls the color the text is rendered at
	m_gameText[0]->SetColor(SDL_Color{ 255, 238, 0, 0 });
	m_gameText[1]->SetColor(SDL_Color{ 0, 239, 225, 0 });
	m_gameText[2]->SetColor(SDL_Color{ 255, 165, 0, 0 });
	m_gameText[3]->SetColor(SDL_Color{ 0, 239, 225, 0 });
	m_gameText[4]->SetColor(SDL_Color{ 0, 239, 225, 0 });
	m_gameText[5]->SetColor(SDL_Color{ 0, 239, 225, 0 });

	//controls what the text says and its world position
	m_gameText[0]->RenderAt("LEVEL 2", 20, 20);
	m_gameText[1]->RenderAt("Hit the ", 225, 75);
	m_gameText[2]->RenderAt("ORANGE ", 380, 75);
	m_gameText[3]->RenderAt("orbs to get launched,", 605, 75);
	m_gameText[4]->RenderAt("you will be launched in whichever direction ", 175, 125);
	m_gameText[5]->RenderAt("you hit them", 450, 175);

	//render character
	m_character->Render();

	//render orb objects
	m_bounceOrb[0]->Render();
	m_dashOrb[0]->Render();
	m_dashOrb[1]->Render();

	//render melee attacks
	m_meleeAttacks[0]->Render();
	m_meleeAttacks[1]->Render();
	m_meleeAttacks[2]->Render();
	m_meleeAttacks[3]->Render();

	//render other objects
	m_exitDoor->Render();
	m_spikes->Render();

	//render borders
	m_border[0]->Render();
	m_border[1]->Render();
	m_border[2]->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	//update character
	m_character->Update(deltaTime, e);
	m_characterPosition = m_character->GetPosition();

	Inputs(e);

#pragma region Orb Collisions

	if (Collisions::Instance()->Box(m_meleeAttacks[0]->GetCollisionBox(), m_bounceOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Left", 1200);
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[1]->GetCollisionBox(), m_bounceOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Right", 1200);
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[2]->GetCollisionBox(), m_bounceOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Down", 1200);
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[3]->GetCollisionBox(), m_bounceOrb[0]->GetCollisionBox()))
	{
		m_character->Bounce(deltaTime, "Up", 1200);
	}


	if (Collisions::Instance()->Box(m_meleeAttacks[0]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Right");
	}
	if (Collisions::Instance()->Box(m_meleeAttacks[0]->GetCollisionBox(), m_dashOrb[1]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Right");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[1]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Left");
	}
	if (Collisions::Instance()->Box(m_meleeAttacks[1]->GetCollisionBox(), m_dashOrb[1]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Left");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[2]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Up");
	}
	if (Collisions::Instance()->Box(m_meleeAttacks[2]->GetCollisionBox(), m_dashOrb[1]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Up");
	}

	if (Collisions::Instance()->Box(m_meleeAttacks[3]->GetCollisionBox(), m_dashOrb[0]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Down");
	}
	if (Collisions::Instance()->Box(m_meleeAttacks[3]->GetCollisionBox(), m_dashOrb[1]->GetCollisionBox()))
	{
		m_character->Dash(deltaTime, "Down");
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
	if (Collisions::Instance()->Box(m_character->GetCollisionBox(), m_exitDoor->GetCollisionBox()))
	{
		gameScreenManager->ChangeScreen(SCREEN_LEVEL3);
	}

#pragma endregion

}

void GameScreenLevel2::Inputs(SDL_Event e)
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