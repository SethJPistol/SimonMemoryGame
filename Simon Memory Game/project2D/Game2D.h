#pragma once

#include <assert.h>
#include "Game.h"
#include "Renderer2D.h"
#include "Sequence.h"
#include "Input.h"

enum eState {
	MENU = 1,
	INITIALPAUSE = 2,
	PAUSED = 3,
	FLASHING = 4,
	PLAYING = 5,
	GAMEOVER = 6,
};

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

	//Restart the game if r is pressed
	void RestartGame(aie::Input* input);

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
	aie::Font*			m_pFontSmall;
	aie::Font*			m_pFontLarge;

	Sequence* m_pDirections;

	int m_nState;

	int nSequenceIterator;
	float nTimer;

	int nScore;
	int nHighScore;

	bool bIsRightFlashing;
	bool bIsLeftFlashing;
	bool bIsDownFlashing;
	bool bIsUpFlashing;
};