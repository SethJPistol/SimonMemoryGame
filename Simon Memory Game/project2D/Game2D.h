#pragma once

#include "Game.h"
#include "Renderer2D.h"
#include "Sequence.h"

class Player;

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

	//Converts the keyboard input codes of arrow keys into numbers 1-4
	//Not sure if this is even needed
	int GetDirectionIndex(int nInputCode);

protected:
	aie::Renderer2D*	m_2dRenderer;

	// Example textures.
	//aie::Texture*		m_texture;
	//aie::Texture*		m_texture2;
	aie::Font*			m_font;

	Sequence* m_pDirections;

	int nSequenceIterator;
};