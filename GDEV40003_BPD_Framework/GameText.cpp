#include "GameText.h"

bool GameText::ttfHasInit = false;

GameText::GameText(SDL_Renderer* renderer, std::string fontPath, unsigned int fontSize)
{
	//Initialise TTF if needed
	if (!InitTTF())
	{
		std::cerr << "Couldn't initialise TTF; error is " << TTF_GetError() << std::endl;
		m_errorEncountered = true;
		return;
	}

	//Set renderer
	this->renderer = renderer;

	//Load the font
	this->LoadFont(fontPath, fontSize);
}

GameText::~GameText()
{
	Destroy();
}

bool GameText::LoadFont(std::string fontPath, unsigned int fontSize)
{
	//TTF has been initialised at this point
	this->font = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (!this->font)
	{
		//No font has been loaded, show error
		std::cerr << "Couldn't load font from path " << fontPath << "; error is " << TTF_GetError() << std::endl;
		m_errorEncountered = true;
		return false;
	}

	return true;
}

void GameText::RenderAt(const std::string& text, int x, int y)
{
	//Errors? Die
	if (m_errorEncountered)
	{
		return;
	}

	//Destroy text if needed
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	//Size the text
	int width;
	int	height;

	//Finds the rendered text size
	TTF_SizeText(font, text.c_str(), &width, &height);

	//Load surface and text
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//Get render rect and rend with it
	SDL_Rect renderRect = { x, y, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);
}

void GameText::SetColor(SDL_Color color)
{
	this->color = color;
}

void GameText::Destroy()
{

}

bool GameText::InitTTF()
{
	//Already inited? Don't bother doing anything else
	if (ttfHasInit)
	{
		return true;
	}

	//Init TTF, return error if not inited correctly
	return (TTF_Init() >= 0);
}