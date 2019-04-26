#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
//#include "Player.h"
#include "Sequence.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	//m_texture = new aie::Texture("./textures/hero.png");
	//m_texture2 = new aie::Texture("./textures/rock_large.png");
	m_font = new aie::Font("./font/consolas.ttf", 24);

	// Create a player object.
	//m_Player = new Player();

	//Create a new sequence
	Sequence* pDirections = new Sequence();
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

	//temp for testing
	if (input->IsKeyDown(aie::INPUT_KEY_UP))
	{
		
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

	// Draw a sprite
	//m_2dRenderer->DrawSprite(m_texture2, 200.0f, 200.0f);

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
	
	// Draw some text.
	float fWindowHeight = (float)application->GetWindowHeight();
	float fWindowWidth = (float)application->GetWindowWidth();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, fWindowHeight - 32.0f);
	m_2dRenderer->DrawText2D(m_font, "PRESS ANY KEY TO BEGIN", (fWindowWidth / 2) - 150.0f, fWindowHeight - 64.0f);
	m_2dRenderer->DrawText2D(m_font, "SCORE:", (fWindowWidth / 2) + (fWindowWidth / 4), fWindowHeight - 96.0f);
	m_2dRenderer->DrawText2D(m_font, "12", (fWindowWidth / 2) + (fWindowWidth / 4), fWindowHeight - 128.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}