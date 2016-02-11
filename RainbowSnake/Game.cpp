#include "Game.h"





Game::Game()
	:actualStateID(END)
	
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Snake", Style::Close, settings);//TODO panel interfejsu
	window.setFramerateLimit(60);
	window.clear();
	window.display();

	if (!font.loadFromFile("data/font.ttf"))
	{
		MessageBox(NULL, "Font not found! Chceck data folder!", "ERROR", NULL);
		return;
	}

	actualStateID=MENU;
	
	
}


Game::~Game()
{
}

void Game::runGame()
{
	actualState = new MenuState(MENU, window, font);
	actualState->init();

	while (actualStateID != END)
	{
		if (actualStateID != actualState->getSTATE_ID())
			changeState();
		
		handleState();
		
	}
	window.close();
}

void Game::changeState()
{
	delete actualState;
	actualState = nullptr;

	switch (actualStateID)
	{
		case MENU:
			actualState = new MenuState(MENU, window, font);
			break;
		case PLAY_STATE:
			cout << "Zmiana na grê" << endl;
			actualState = new PlayState(PLAY_STATE, window, font);
			break;
		case FAILURE:
			Image screenShot = window.capture();
			actualState = new FailureState(FAILURE, window, font, screenShot);
			break;
	}
	
	actualState->init();
}

void Game::handleState()
{	
	actualStateID = actualState->handleEvents(event);
	actualState->update();
	actualState->render();
}