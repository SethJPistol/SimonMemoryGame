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
	m_font = new aie::Font("./font/consolas.ttf", 24);

	//Create a new sequence
	m_pDirections = new Sequence();

	//Set sequence count to 0
	nSequenceIterator = 0;
	bIsRightFlashing = false;
	bIsLeftFlashing = false;
	bIsDownFlashing = false;
	bIsUpFlashing = false;
}

Game2D::~Game2D()
{
	// Delete player.
	//delete m_Player;
	//m_Player = nullptr;

	// Deleted the textures.
	delete m_font;
	//delete m_texture;
	//delete m_texture2;

	// Delete the renderer.
	delete m_2dRenderer;
}

void Game2D::Update(float deltaTime)
{
	aie::Input* input = aie::Input::GetInstance();

	//If an arrow just flashed, stop it from flashing again
	bIsRightFlashing = false;
	bIsLeftFlashing = false;
	bIsDownFlashing = false;
	bIsUpFlashing = false;

	//If right arrow key, check if correct
	if (input->WasKeyPressed(aie::INPUT_KEY_RIGHT))
	{
		bool bCorrectDirection = m_pDirections->CheckDirection(nSequenceIterator, RIGHT);

		if (bCorrectDirection)
		{
			//Animate the sprite
			bIsRightFlashing = true;
			
			++nSequenceIterator;

			//If end of the sequence
			if (nSequenceIterator >= m_pDirections->SequenceCount())
			{
				//Reset the iterator
				nSequenceIterator = 0;
				//Start the new sequence flashes here
			}
		}
		else
		{
			//Gameover
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

			++nSequenceIterator;

			//If end of the sequence
			if (nSequenceIterator >= m_pDirections->SequenceCount())
			{
				//Reset the iterator
				nSequenceIterator = 0;
				//Start the new sequence flashes
			}
		}
		else
		{
			//Gameover
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

			++nSequenceIterator;

			//If end of the sequence
			if (nSequenceIterator >= m_pDirections->SequenceCount())
			{
				//Reset the iterator
				nSequenceIterator = 0;
				//Start the new sequence flashes
			}
		}
		else
		{
			//Gameover
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

			++nSequenceIterator;

			//If end of the sequence
			if (nSequenceIterator >= m_pDirections->SequenceCount())
			{
				//Reset the iterator
				nSequenceIterator = 0;
				//Start the new sequence flashes
			}
		}
		else
		{
			//Gameover
		}
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
	
	float fWindowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	//HUD text
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, fWindowHeight - 32.0f);
	m_2dRenderer->DrawText2D(m_font, "PRESS ANY KEY TO BEGIN", 65.0f, fWindowHeight - 64.0f);
	m_2dRenderer->DrawText2D(m_font, "SCORE:", 325.0f, fWindowHeight - 125.0f);
	m_2dRenderer->DrawText2D(m_font, "12", 350.0f, fWindowHeight - 150.0f);

	//Arrow sprites
	if (bIsRightFlashing)
		m_2dRenderer->DrawSprite(m_pRightArrowFlashTexture, 325.0f, fWindowHeight - 300.0f);
	else
		m_2dRenderer->DrawSprite(m_pRightArrowTexture, 325.0f, fWindowHeight - 300.0f);

	if (bIsLeftFlashing)
		m_2dRenderer->DrawSprite(m_pLeftArrowFlashTexture, 75.0f, fWindowHeight - 300.0f);
	else
		m_2dRenderer->DrawSprite(m_pLeftArrowTexture, 75.0f, fWindowHeight - 300.0f);

	if (bIsDownFlashing)
		m_2dRenderer->DrawSprite(m_pDownArrowFlashTexture, 200.0f, fWindowHeight - 425.0f);
	else
		m_2dRenderer->DrawSprite(m_pDownArrowTexture, 200.0f, fWindowHeight - 425.0f);

	if (bIsUpFlashing)
		m_2dRenderer->DrawSprite(m_pUpArrowFlashTexture, 200.0f, fWindowHeight - 175.0f);
	else
		m_2dRenderer->DrawSprite(m_pUpArrowTexture, 200.0f, fWindowHeight - 175.0f);
	
	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}

int Game2D::GetDirectionIndex(int nInputCode)
{
	//Only allow arrow key codes
	if (nInputCode > 261 && nInputCode < 266)
		return nInputCode - 261;
	else
		return 0;
}