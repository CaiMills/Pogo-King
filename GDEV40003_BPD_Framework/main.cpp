#include "SDL.h"
#include "constants.h"
#include <iostream>
#include "SDL_image.h"
#include "commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "SDL_ttf.h"
#include "SDL_timer.h"

using namespace std;

bool InitSDL();
void CloseSDL();
bool Update();

void Render();

Texture2D* m_texture = nullptr;

//Global variables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;

GameScreenManager* game_screen_manager;
Uint32 g_old_time;

bool InitSDL()
{
	//Setup SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);



		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		//initialises the use of audio
		//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		//{
		//	cout << "Mixer could not init. Error: " << Mix_GetError();
		//}

		SDL_JoystickOpen(1); //Allows for joystick compatibility

		TTF_Init(); //initiallises the TTF library (game text)

		//The initalization was successful
		return true;
	}
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//Update the screen
	SDL_RenderPresent(g_renderer);
}



void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//quit SDL subsystems
	SDL_Quit();
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	bool quit = false;

	//Event Handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;

	return false;
}

int main(int argc, char* argv[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MAINMENU);

		//set the time
		g_old_time = SDL_GetTicks();

		//flag to check if we wish to quit
		bool quit = false;

		//Game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

