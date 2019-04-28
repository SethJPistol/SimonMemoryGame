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

	//Textures
	aie::Texture*		m_pRightArrowTexture;
	aie::Texture*		m_pLeftArrowTexture;
	aie::Texture*		m_pDownArrowTexture;
	aie::Texture*		m_pUpArrowTexture;
	aie::Texture*		m_pRightArrowFlashTexture;
	aie::Texture*		m_pLeftArrowFlashTexture;
	aie::Texture*		m_pDownArrowFlashTexture;
	aie::Texture*		m_pUpArrowFlashTexture;
	aie::Font*			m_font;

	Sequence* m_pDirections;

	int nSequenceIterator;
	bool bIsRightFlashing;
	bool bIsLeftFlashing;
	bool bIsDownFlashing;
	bool bIsUpFlashing;
};