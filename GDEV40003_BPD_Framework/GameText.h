#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include "commons.h"
#include "SDL_ttf.h"

class GameText
{
public:

	GameText(SDL_Renderer* renderer, std::string fontPath, unsigned int fontSize);
	~GameText();

	bool LoadFont(std::string fontPath, unsigned int fontSize);

	void RenderAt(const std::string& text, int x, int y);
	void SetColor(SDL_Color color);

protected:

	SDL_Texture* texture = nullptr;
	TTF_Font* font;
	SDL_Color color{ 255, 255, 255, 255 };
	SDL_Renderer* renderer;

private:

	void Destroy();

	static bool ttfHasInit;
	static bool InitTTF();

	bool m_errorEncountered = false;
};

