#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

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
	m_pFont = new aie::Font("./font/consolas.ttf", 24);

	//Create a new sequence
	m_pDirections = new Sequence();

	//Set sequence count and timer to 0
	nSequenceIterator = 0;
	nTimer = 0.0f;

	//Start the game with the sequence flashing
	bIsSequenceFlashing = true;
	bHasLost = false;

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
	delete m_pFont;
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

	//Skip if gameover
	if (!bHasLost)
	{
		//Checks if the sequence is meant to be flashing
		if (bIsSequenceFlashing)
		{
			//If end of the sequence
			if (nSequenceIterator >= m_pDirections->SequenceCount())
			{
				nSequenceIterator = 0;
				bIsSequenceFlashing = false;
			}

			//Timer check so that it only flashes when another flash is done
			else if (nTimer > 0.5f)
			{
				switch ((*m_pDirections)[nSequenceIterator])
				{
					//Right
				case 1:
					//Animate the sprite
					bIsRightFlashing = true;
					//Reset the flash timer
					nTimer = 0.0f;
					++nSequenceIterator;
					break;
					//Left
				case 2:
					//Animate the sprite
					bIsLeftFlashing = true;
					//Reset the flash timer
					nTimer = 0.0f;
					++nSequenceIterator;
					break;
					//Down
				case 3:
					//Animate the sprite
					bIsDownFlashing = true;
					//Reset the flash timer
					nTimer = 0.0f;
					++nSequenceIterator;
					break;
					//Up
				case 4:
					//Animate the sprite
					bIsUpFlashing = true;
					//Reset the flash timer
					nTimer = 0.0f;
					++nSequenceIterator;
					break;
				}
			}
		}
		//Sequence isn't flashing, so allow input
		else
		{
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
						//Start the new sequence flashes here
						bIsSequenceFlashing = true;
						//Add to score
						++nScore;
					}
				}
				else
				{
					//Gameover
					bHasLost = true;
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
						//Start the new sequence flashes here
						bIsSequenceFlashing = true;
						//Add to score
						++nScore;
					}
				}
				else
				{
					//Gameover
					bHasLost = true;
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
						//Start the new sequence flashes here
						bIsSequenceFlashing = true;
						//Add to score
						++nScore;
					}
				}
				else
				{
					//Gameover
					bHasLost = true;
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
						//Start the new sequence flashes here
						bIsSequenceFlashing = true;
						//Add to score
						++nScore;
					}
				}
				else
				{
					//Gameover
					bHasLost = true;
				}
			}
		}
	}

	//Update the high score
	if (nScore > nHighScore)
	{
		nHighScore = nScore;
	}

	//Restart the game if r is pressed
	if (input->WasKeyPressed(aie::INPUT_KEY_R))
	{
		bHasLost = false;
		bIsRightFlashing = false;
		bIsLeftFlashing = false;
		bIsDownFlashing = false;
		bIsUpFlashing = false;
		bIsSequenceFlashing = true;
		nTimer = 0.0f;
		nSequenceIterator = 0;
		nScore = 0;
		m_pDirections->SequenceClear();
		m_pDirections->AddDirection();
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
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	// Draw a thin line.
	//m_2dRenderer->DrawLine(150.0f, 400.0f, 250.0f, 500.0f, 2.0f);

	// Draw a moving purple circle.
	//m_2dRenderer->SetRenderColour(1.0f, 0.0f, 1.0f, 1.0f);
	//m_2dRenderer->DrawCircle(sin(time) * 100.0f + 450.0f, 200.0f, 50.0f);

	// Draw a rotating sprite with no texture, coloured yellow.
	//m_2dRenderer->SetRenderColour(1.0f, 1.0f, 0.0f, 1.0f);
	//m_2dRenderer->DrawSprite(nullptr, 700.0f, 200.0f, 50.0f, 50.0f, time);
	//m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	// Demonstrate animation.
	//float animSpeed = 10.0f;
	//int frame = ((int)(time * animSpeed) % 6);
	//float size = 1.0f / 6.0f;
	//m_2dRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	//m_2dRenderer->DrawSprite(m_texture, 900.0f, 200.0f, 100.0f, 100.0f);
	//m_2dRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);
	
	//HUD text
	float fWindowHeight = (float)application->GetWindowHeight();
	//char fps[32];
	char score[3];
	char highscore[3];
	//sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	sprintf_s(score, 3, "%i", nScore);
	sprintf_s(highscore, 3, "%i", nHighScore);
	//m_2dRenderer->DrawText2D(m_pFont, fps, 15.0f, fWindowHeight - 32.0f);
	//m_2dRenderer->DrawText2D(m_pFont, "PRESS ANY KEY TO BEGIN", 65.0f, fWindowHeight - 64.0f);
	m_2dRenderer->DrawText2D(m_pFont, "HIGH SCORE:", 290.0f, fWindowHeight - 50.0f);
	m_2dRenderer->DrawText2D(m_pFont, highscore, 350.0f, fWindowHeight - 75.0f);
	m_2dRenderer->DrawText2D(m_pFont, "SCORE:", 325.0f, fWindowHeight - 325.0f);
	m_2dRenderer->DrawText2D(m_pFont, score, 350.0f, fWindowHeight - 350.0f);

	if (bHasLost)
	{
		m_2dRenderer->DrawText2D(m_pFont, "YOU HAVE LOST", 112.0f, fWindowHeight - 75.0f);
		m_2dRenderer->DrawText2D(m_pFont, "PRESS R TO RESTART", 85.0f, fWindowHeight - 100.0f);
	}

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
	
	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}