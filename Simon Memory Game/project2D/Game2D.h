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
	aie::Font*			m_pFont;

	Sequence* m_pDirections;

	int nSequenceIterator;
	float nTimer;
	bool bIsSequenceFlashing;
	bool bHasLost;

	int nScore;
	int nHighScore;

	bool bIsRightFlashing;
	bool bIsLeftFlashing;
	bool bIsDownFlashing;
	bool bIsUpFlashing;
};