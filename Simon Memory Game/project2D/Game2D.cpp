#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	//Create the arrow textures
	m_pRightArrowTexture = new aie::Texture("./textures/rightArrow.png");
	m_pLeftArrowTexture = new aie::Texture("./textures/leftArrow.png");
	m_pDownArrowTexture = new aie::Texture("./textures/downArrow.png");
	m_pUpArrowTexture = new aie::Texture("./textures/upArrow.png");
	m_pRightArrowFlashTexture = new aie::Texture("./textures/rightArrowFlash.png");
	m_pLeftArrowFlashTexture = new aie::Texture("./textures/leftArrowFlash.png");
	m_pDownArrowFlashTexture = new aie::Texture("./textures/downArrowFlash.png");
	m_pUpArrowFlashTexture = new aie::Texture("./textures/upArrowFlash.png");
	m_pFontSmall = new aie::Font("./font/consolas.ttf", 24);
	m_pFontLarge = new aie::Font("./font/consolas.ttf", 44);

	//Create a new sequence
	m_pDirections = new Sequence();

	//Set sequence count and timer to 0
	nSequenceIterator = 0;
	nTimer = 0.0f;
	
	//Start the game on the menu
	m_nState = MENU;

	nScore = 0;
	nHighScore = 0;

	bIsRightFlashing = false;
	bIsLeftFlashing = false;
	bIsDownFlashing = false;
	bIsUpFlashing = false;
}

Game2D::~Game2D()
{
	//Delete the sequence
	delete m_pDirections;
	m_pDirections = nullptr;

	//Delete the textures
	delete m_pFontSmall;
	delete m_pFontLarge;
	delete m_pRightArrowTexture;
	delete m_pLeftArrowTexture;
	delete m_pDownArrowTexture;
	delete m_pUpArrowTexture;
	delete m_pRightArrowFlashTexture;
	delete m_pLeftArrowFlashTexture;
	delete m_pDownArrowFlashTexture;
	delete m_pUpArrowFlashTexture;

	//Delete the renderer
	delete m_2dRenderer;
}

void Game2D::Update(float deltaTime)
{	
	aie::Input* input = aie::Input::GetInstance();
	aie::Application* application = aie::Application::GetInstance();
	float fWindowHeight = (float)application->GetWindowHeight();

	assert(m_pDirections);

	switch (m_nState)
	{
	case MENU:
		if (input->WasKeyPressed(aie::INPUT_KEY_ENTER))
		{
			m_nState = INITIALPAUSE;
		}
		//Check if the play button has been clicked
		if (input->WasMouseButtonPressed(0) 
			&& input->GetMouseX() < 283 
			&& input->GetMouseX() > 13 
			&& input->GetMouseY() < (fWindowHeight - 128) 
			&& input->GetMouseY() > (fWindowHeight - 158))
		{
			m_nState = INITIALPAUSE;
		}
		break;

	case INITIALPAUSE:
		if (input->WasKeyPressed(aie::INPUT_KEY_P))
		{
			m_nState = FLASHING;
		}
		break;

	case PAUSED:
		if (input->WasKeyPressed(aie::INPUT_KEY_P))
		{
			m_nState = PLAYING;
		}
		break;

	case FLASHING:
		//This adds time to the timer every frame
		nTimer += deltaTime;

		//If an arrow just flashed, stop it from flashing again
		if (nTimer > 0.15f)
		{
			bIsRightFlashing = false;
			bIsLeftFlashing = false;
			bIsDownFlashing = false;
			bIsUpFlashing = false;
		}

		//If the player presses p, pause
		if (input->WasKeyPressed(aie::INPUT_KEY_P))
		{
			m_nState = INITIALPAUSE;
		}

		//If end of the sequence
		if (nSequenceIterator >= m_pDirections->SequenceCount())
		{
			nSequenceIterator = 0;
			m_nState = PLAYING;
		}

		//Timer check so that it only flashes when another flash is done
		else if (nTimer > 0.5f)
		{
			//Sees which direction is in the current sequence slot
			switch ((*m_pDirections)[nSequenceIterator])
			{
			case RIGHT:
				//Animate the sprite
				bIsRightFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;
				++nSequenceIterator;
				break;
			case LEFT:
				//Animate the sprite
				bIsLeftFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;
				++nSequenceIterator;
				break;
			case DOWN:
				//Animate the sprite
				bIsDownFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;
				++nSequenceIterator;
				break;
			case UP:
				//Animate the sprite
				bIsUpFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;
				++nSequenceIterator;
				break;
			}
		}
		break;

	case PLAYING:
		//This adds time to the timer every frame
		nTimer += deltaTime;

		//If an arrow just flashed, stop it from flashing again
		if (nTimer > 0.15f)
		{
			bIsRightFlashing = false;
			bIsLeftFlashing = false;
			bIsDownFlashing = false;
			bIsUpFlashing = false;
		}

		//Check if they press r to restart
		RestartGame(input);

		//If the player presses p, pause
		if (input->WasKeyPressed(aie::INPUT_KEY_P))
		{
			m_nState = PAUSED;
		}

		//If right arrow key, check if correct
		if (input->WasKeyPressed(aie::INPUT_KEY_RIGHT))
		{
			bool bCorrectDirection = m_pDirections->CheckDirection(nSequenceIterator, RIGHT);

			if (bCorrectDirection)
			{
				//Animate the sprite
				bIsRightFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;

				++nSequenceIterator;

				//If end of the sequence
				if (nSequenceIterator >= m_pDirections->SequenceCount())
				{
					//Reset the iterator
					nSequenceIterator = 0;
					//Add a new direction to the sequence
					m_pDirections->AddDirection();
					//Start the new sequence flashes
					m_nState = FLASHING;
					//Add to score
					++nScore;
				}
			}
			else
			{
				m_nState = GAMEOVER;
			}
		}

		//If left arrow key, check if correct
		if (input->WasKeyPressed(aie::INPUT_KEY_LEFT))
		{
			bool bCorrectDirection = m_pDirections->CheckDirection(nSequenceIterator, LEFT);

			if (bCorrectDirection)
			{
				//Animate the sprite
				bIsLeftFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;

				++nSequenceIterator;

				//If end of the sequence
				if (nSequenceIterator >= m_pDirections->SequenceCount())
				{
					//Reset the iterator
					nSequenceIterator = 0;
					//Add a new direction to the sequence
					m_pDirections->AddDirection();
					//Start the new sequence flashes
					m_nState = FLASHING;
					//Add to score
					++nScore;
				}
			}
			else
			{
				m_nState = GAMEOVER;
			}
		}

		//If down arrow key, check if correct
		if (input->WasKeyPressed(aie::INPUT_KEY_DOWN))
		{
			bool bCorrectDirection = m_pDirections->CheckDirection(nSequenceIterator, DOWN);

			if (bCorrectDirection)
			{
				//Animate the sprite
				bIsDownFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;

				++nSequenceIterator;

				//If end of the sequence
				if (nSequenceIterator >= m_pDirections->SequenceCount())
				{
					//Reset the iterator
					nSequenceIterator = 0;
					//Add a new direction to the sequence
					m_pDirections->AddDirection();
					//Start the new sequence flashes
					m_nState = FLASHING;
					//Add to score
					++nScore;
				}
			}
			else
			{
				m_nState = GAMEOVER;
			}
		}

		//If up arrow key, check if correct
		if (input->WasKeyPressed(aie::INPUT_KEY_UP))
		{
			bool bCorrectDirection = m_pDirections->CheckDirection(nSequenceIterator, UP);

			if (bCorrectDirection)
			{
				//Animate the sprite
				bIsUpFlashing = true;
				//Reset the flash timer
				nTimer = 0.0f;

				++nSequenceIterator;

				//If end of the sequence
				if (nSequenceIterator >= m_pDirections->SequenceCount())
				{
					//Reset the iterator
					nSequenceIterator = 0;
					//Add a new direction to the sequence
					m_pDirections->AddDirection();
					//Start the new sequence flashes
					m_nState = FLASHING;
					//Add to score
					++nScore;
				}
			}
			else
			{
				m_nState = GAMEOVER;
			}
		}

		//Update the high score
		if (nScore > nHighScore)
		{
			nHighScore = nScore;
		}
		break;

	case GAMEOVER:
		//Check if they press r to restart
		RestartGame(input);
		break;

	default:
		assert(0);
		break;
	}

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	assert(m_pRightArrowTexture);
	assert(m_pLeftArrowTexture);
	assert(m_pDownArrowTexture);
	assert(m_pUpArrowTexture);
	assert(m_pRightArrowFlashTexture);
	assert(m_pLeftArrowFlashTexture);
	assert(m_pDownArrowFlashTexture);
	assert(m_pUpArrowFlashTexture);
	assert(m_pFontSmall);
	assert(m_pFontLarge);

	aie::Application* application = aie::Application::GetInstance();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	float fWindowHeight = (float)application->GetWindowHeight();
	char score[3];
	char highscore[3];

	switch (m_nState)
	{
	case MENU:
		m_2dRenderer->DrawText2D(m_pFontLarge, "SIMON MEMORY GAME", 15.0f, fWindowHeight - 50.0f);
		m_2dRenderer->SetRenderColour(0, 0, 150);
		m_2dRenderer->DrawBox(148.0f, fWindowHeight - 143.0f, 270, 30);
		m_2dRenderer->SetRenderColour(255, 255, 255);
		m_2dRenderer->DrawText2D(m_pFontSmall, "-PRESS ENTER TO PLAY", 15.0f, fWindowHeight - 150.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "-PRESS ESC TO QUIT", 15.0f, fWindowHeight - 200.0f);
		break;

	case INITIALPAUSE:
		//HUD
		m_2dRenderer->DrawText2D(m_pFontSmall, "THE GAME IS PAUSED", 85.0f, fWindowHeight - 425.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "PRESS P TO CONTINUE", 80.0f, fWindowHeight - 450.0f);
		sprintf_s(score, 3, "%i", nScore);
		sprintf_s(highscore, 3, "%i", nHighScore);
		m_2dRenderer->DrawText2D(m_pFontSmall, "HIGH SCORE:", 290.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, highscore, 350.0f, fWindowHeight - 75.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "SCORE:", 25.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, score, 50.0f, fWindowHeight - 75.0f);

		//Arrow sprites
		if (bIsRightFlashing)
			m_2dRenderer->DrawSprite(m_pRightArrowFlashTexture, 325.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pRightArrowTexture, 325.0f, fWindowHeight - 200.0f);

		if (bIsLeftFlashing)
			m_2dRenderer->DrawSprite(m_pLeftArrowFlashTexture, 75.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pLeftArrowTexture, 75.0f, fWindowHeight - 200.0f);

		if (bIsDownFlashing)
			m_2dRenderer->DrawSprite(m_pDownArrowFlashTexture, 200.0f, fWindowHeight - 325.0f);
		else
			m_2dRenderer->DrawSprite(m_pDownArrowTexture, 200.0f, fWindowHeight - 325.0f);

		if (bIsUpFlashing)
			m_2dRenderer->DrawSprite(m_pUpArrowFlashTexture, 200.0f, fWindowHeight - 75.0f);
		else
			m_2dRenderer->DrawSprite(m_pUpArrowTexture, 200.0f, fWindowHeight - 75.0f);

		break;

	case PAUSED:
		//HUD
		m_2dRenderer->DrawText2D(m_pFontSmall, "THE GAME IS PAUSED", 85.0f, fWindowHeight - 425.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "PRESS P TO CONTINUE", 80.0f, fWindowHeight - 450.0f);
		sprintf_s(score, 3, "%i", nScore);
		sprintf_s(highscore, 3, "%i", nHighScore);
		m_2dRenderer->DrawText2D(m_pFontSmall, "HIGH SCORE:", 290.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, highscore, 350.0f, fWindowHeight - 75.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "SCORE:", 25.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, score, 50.0f, fWindowHeight - 75.0f);

		//Arrow sprites
		if (bIsRightFlashing)
			m_2dRenderer->DrawSprite(m_pRightArrowFlashTexture, 325.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pRightArrowTexture, 325.0f, fWindowHeight - 200.0f);

		if (bIsLeftFlashing)
			m_2dRenderer->DrawSprite(m_pLeftArrowFlashTexture, 75.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pLeftArrowTexture, 75.0f, fWindowHeight - 200.0f);

		if (bIsDownFlashing)
			m_2dRenderer->DrawSprite(m_pDownArrowFlashTexture, 200.0f, fWindowHeight - 325.0f);
		else
			m_2dRenderer->DrawSprite(m_pDownArrowTexture, 200.0f, fWindowHeight - 325.0f);

		if (bIsUpFlashing)
			m_2dRenderer->DrawSprite(m_pUpArrowFlashTexture, 200.0f, fWindowHeight - 75.0f);
		else
			m_2dRenderer->DrawSprite(m_pUpArrowTexture, 200.0f, fWindowHeight - 75.0f);

		break;

	case FLASHING:
		//HUD
		sprintf_s(score, 3, "%i", nScore);
		sprintf_s(highscore, 3, "%i", nHighScore);
		m_2dRenderer->DrawText2D(m_pFontSmall, "HIGH SCORE:", 290.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, highscore, 350.0f, fWindowHeight - 75.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "SCORE:", 25.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, score, 50.0f, fWindowHeight - 75.0f);

		//Arrow sprites
		if (bIsRightFlashing)
			m_2dRenderer->DrawSprite(m_pRightArrowFlashTexture, 325.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pRightArrowTexture, 325.0f, fWindowHeight - 200.0f);

		if (bIsLeftFlashing)
			m_2dRenderer->DrawSprite(m_pLeftArrowFlashTexture, 75.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pLeftArrowTexture, 75.0f, fWindowHeight - 200.0f);

		if (bIsDownFlashing)
			m_2dRenderer->DrawSprite(m_pDownArrowFlashTexture, 200.0f, fWindowHeight - 325.0f);
		else
			m_2dRenderer->DrawSprite(m_pDownArrowTexture, 200.0f, fWindowHeight - 325.0f);

		if (bIsUpFlashing)
			m_2dRenderer->DrawSprite(m_pUpArrowFlashTexture, 200.0f, fWindowHeight - 75.0f);
		else
			m_2dRenderer->DrawSprite(m_pUpArrowTexture, 200.0f, fWindowHeight - 75.0f);

		break;

	case PLAYING:
		//HUD
		sprintf_s(score, 3, "%i", nScore);
		sprintf_s(highscore, 3, "%i", nHighScore);
		m_2dRenderer->DrawText2D(m_pFontSmall, "HIGH SCORE:", 290.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, highscore, 350.0f, fWindowHeight - 75.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "SCORE:", 25.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, score, 50.0f, fWindowHeight - 75.0f);

		//Arrow sprites
		if (bIsRightFlashing)
			m_2dRenderer->DrawSprite(m_pRightArrowFlashTexture, 325.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pRightArrowTexture, 325.0f, fWindowHeight - 200.0f);

		if (bIsLeftFlashing)
			m_2dRenderer->DrawSprite(m_pLeftArrowFlashTexture, 75.0f, fWindowHeight - 200.0f);
		else
			m_2dRenderer->DrawSprite(m_pLeftArrowTexture, 75.0f, fWindowHeight - 200.0f);

		if (bIsDownFlashing)
			m_2dRenderer->DrawSprite(m_pDownArrowFlashTexture, 200.0f, fWindowHeight - 325.0f);
		else
			m_2dRenderer->DrawSprite(m_pDownArrowTexture, 200.0f, fWindowHeight - 325.0f);

		if (bIsUpFlashing)
			m_2dRenderer->DrawSprite(m_pUpArrowFlashTexture, 200.0f, fWindowHeight - 75.0f);
		else
			m_2dRenderer->DrawSprite(m_pUpArrowTexture, 200.0f, fWindowHeight - 75.0f);

		break;

	case GAMEOVER:
		//HUD
		m_2dRenderer->DrawText2D(m_pFontSmall, "YOU HAVE LOST", 118.0f, fWindowHeight - 425.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "PRESS R TO RESTART", 91.0f, fWindowHeight - 450.0f);
		sprintf_s(score, 3, "%i", nScore);
		sprintf_s(highscore, 3, "%i", nHighScore);
		m_2dRenderer->DrawText2D(m_pFontSmall, "HIGH SCORE:", 290.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, highscore, 350.0f, fWindowHeight - 75.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, "SCORE:", 25.0f, fWindowHeight - 50.0f);
		m_2dRenderer->DrawText2D(m_pFontSmall, score, 50.0f, fWindowHeight - 75.0f);

		//Arrow sprites
		m_2dRenderer->DrawSprite(m_pRightArrowTexture, 325.0f, fWindowHeight - 200.0f);
		m_2dRenderer->DrawSprite(m_pLeftArrowTexture, 75.0f, fWindowHeight - 200.0f);
		m_2dRenderer->DrawSprite(m_pDownArrowTexture, 200.0f, fWindowHeight - 325.0f);
		m_2dRenderer->DrawSprite(m_pUpArrowTexture, 200.0f, fWindowHeight - 75.0f);
		break;

	default:
		assert(0);
		break;
	}
	
	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}

void Game2D::RestartGame(aie::Input* input)
{
	if (input->WasKeyPressed(aie::INPUT_KEY_R))
	{
		assert(m_pDirections);
		m_nState = FLASHING;
		bIsRightFlashing = false;
		bIsLeftFlashing = false;
		bIsDownFlashing = false;
		bIsUpFlashing = false;
		nTimer = 0.0f;
		nSequenceIterator = 0;
		nScore = 0;
		m_pDirections->SequenceClear();
		m_pDirections->AddDirection();
	}
}